#pragma once
#include <math.h>
#include "picture_tab.h"
#include "exposure_dialog.h"

#using <System.dll>
#using <System.Xml.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;

// xml pictures can contain either float or int data
public ref class cXmlPictureTab : public cPictureTab
{

public:

	cXmlPictureTab(String ^fileName, System::Drawing::Size ^dim) :
		cPictureTab(fileName, dim)
    {		

		if(exposureDialog == nullptr) {
			
			exposureDialog = gcnew cExposureDialog();
		}
		
		ToolStripMenuItem ^mnuExposure = gcnew ToolStripMenuItem(L"Exposure");
		mnuExposure->Click += gcnew EventHandler(this, &cXmlPictureTab::mnuExposure_Click);

		ContextMenuStrip->Items->Add(mnuExposure);

    }

	void SetExposure(float exposure) 
	{
	
		this->exposure = exposure;

		int x = 0;
		int y = 0;

		for(int i = 0; i < floatData->Length; i += nrChannels) {

			float rgba[4] = {0,0,0,0};

			// map data values into displayable range of [0..1]
			for(int j = 0; j < nrChannels; j++) {

				rgba[j] = 1 - exp(abs(floatData[i + j]) * exposure);
			}

			Color color = Color::FromArgb(int(rgba[0] * 255), 
										  int(rgba[1] * 255), 
										  int(rgba[2] * 255));
			
			bitmap->SetPixel(x, globalFlip ? y : height - y - 1, color);

			if(++x == width) {
				x = 0;
				y++;
			}
		}

	}
	// return pixel values for a specified position
	virtual void GetPixelInfo(Point pos, cPixelInfo ^info) override {

		if(pos.X < 0 || pos.X >= bitmap->Width || pos.Y < 0 || pos.Y >= bitmap->Height) {

			info->R = 0;
			info->G = 0;
			info->B = 0;
			info->A = 0;

			return;
		}

		if(globalFlip == false) {

			pos.Y = height - pos.Y - 1;
		}

		int offset = (pos.Y * width + pos.X) * nrChannels;

		float rgba[4] = {0,0,0,0};

		for(int j = 0; j < nrChannels; j++) {

			rgba[j] = floatData[offset + j];
		}

		info->R = rgba[0];
		info->G = rgba[1];
		info->B = rgba[2];
		info->A = rgba[3];

	}



protected:

	virtual void LoadImage(String ^fileName) override {

		exposure = -2;

		ParseXmlImage(fileName);
		
		bitmap = gcnew Bitmap(width, height, Imaging::PixelFormat::Format32bppArgb);

		SetExposure(exposure);

	}

	void ParseXmlImage(String ^fileName) 
	{
		String ^channelOrder;
		String ^dataType;
		String ^dataFileName;

		// parse xml header
		imageXMLParser = gcnew XmlTextReader(fileName);

		do {
        
			if(imageXMLParser->NodeType == XmlNodeType::Element) {
				
				if(imageXMLParser->Name == L"HorizontalRes") {

					width = imageXMLParser->ReadElementContentAsInt();

				}
				else if(imageXMLParser->Name == L"VerticalRes") {

					height = imageXMLParser->ReadElementContentAsInt();

				}
				else if(imageXMLParser->Name == L"NrChannels") {

					nrChannels = imageXMLParser->ReadElementContentAsInt();

				}
				else if(imageXMLParser->Name == L"ChannelOrder") {

					channelOrder = imageXMLParser->ReadElementContentAsString();						

				}
				else if(imageXMLParser->Name == L"DataType") {

					dataType = imageXMLParser->ReadElementContentAsString();

				}
				else if(imageXMLParser->Name == L"DataFile") {

					dataFileName = imageXMLParser->ReadElementContentAsString();

				}

			}
          
        } while (imageXMLParser->Read() == true);

		// channel order can be any permutation of "RGBA" depending on the number of channels
		// for example: 
		// "ARGB", "BGRA": for 4 channel images 
		// "RG", "RA": for 2 channel images
		// If a single channel is specified multiple times, only the last occurence will
		// be displayed.
		// e.g: "RRGA", will map the second data channel to Red while the Blue channel
		// will remain zero for every pixel.
		channelOffset = gcnew cli::array<int>(4);
		channelOffset->Initialize();

		for(int i = 0; i < channelOrder->Length; i++) {
		
			if(channelOrder->Substring(i,1)->ToUpper()->CompareTo(L"R") == 0) {

				channelOffset[i] = 0;

			} else if(channelOrder->Substring(i,1)->ToUpper()->CompareTo(L"G") == 0) {

				channelOffset[i] = 1;

			} else if(channelOrder->Substring(i,1)->ToUpper()->CompareTo(L"B") == 0) {

				channelOffset[i] = 2;

			} else if(channelOrder->Substring(i,1)->ToUpper()->CompareTo(L"A") == 0) {

				channelOffset[i] = 3;
			}
			
		}

		// path to dumped data is relative to the location of the xml header file
		String ^fullDataFileName = Path::GetDirectoryName( fileName ) + L"\\" + dataFileName; 

		// read dumped data
		FileStream ^fileStream = gcnew FileStream(fullDataFileName, FileMode::Open);

		BinaryReader ^binaryReader = gcnew BinaryReader(fileStream);

		int nrActiveChannels = channelOrder->Length;

		int size = width * height;
		int dataSize = size * nrActiveChannels;

		floatData = gcnew cli::array<float>(dataSize);
	
		for(int i = 0; i < size; i++) {

			float tempBuf[4] = {0,0,0,0};

			for(int k = 0; k < nrChannels; k++) {

				if(dataType == L"float") tempBuf[k] = binaryReader->ReadSingle();
				if(dataType == L"int") tempBuf[k] = float(binaryReader->ReadInt32());

			}

			int pos = i * nrActiveChannels;

			for(int k = 0; k < nrActiveChannels; k++) {

				floatData[pos + k] = tempBuf[channelOffset[k]];
			}
			
		}

		fileStream->Close();

		nrChannels = nrActiveChannels;
		
	}

	void mnuExposure_Click(Object ^sender, EventArgs ^e) {
		
		exposureDialog->exposure = exposure;

		if(exposureDialog->ShowDialog() == DialogResult::OK) {

			SetExposure(exposureDialog->exposure);

			panel->Refresh();

		} 

	}

protected:

	int width, height, nrChannels;
	cli::array<float> ^floatData;

	cli::array<int> ^channelOffset;

	float exposure;
	
	static cExposureDialog ^exposureDialog;

	XmlTextReader ^imageXMLParser;

};
