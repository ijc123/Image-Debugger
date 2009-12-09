#pragma once
#include "byte_picture_tab.h"
#include "xml_picture_tab.h"
#include "rgba_info.h"
#include "location_info.h"
#include "about_dialog.h"

#define DEFAULT_CANVAS_WIDTH	1024
#define DEFAULT_CANVAS_HEIGHT	768

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class cImageDebugger : public Form
{


public:

    cImageDebugger()
    {
		Form::Text = L"Image Debugger";
		Form::AutoSize = true;
		Form::MaximizeBox = false;
		Form::FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

		tabSize = gcnew System::Drawing::Size(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT);

		// menu items
		mnuMain = gcnew MenuStrip();
		mnuMain->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
		mnuMain->Location = System::Drawing::Point(0, 0);
		mnuMain->Name = L"mnuMain";
		mnuMain->Size = System::Drawing::Size(292, 29);
		mnuMain->TabIndex = 0;
		mnuMain->Text = L"mnuMain";
	
		mnuFile = gcnew ToolStripMenuItem(L"File");
		mnuOpen = gcnew ToolStripMenuItem(L"Open");
		mnuOpen->Click += gcnew System::EventHandler(this, &cImageDebugger::mnuOpen_Click);

		mnuExit = gcnew ToolStripMenuItem(L"Exit");
		mnuExit->Click += gcnew System::EventHandler(this, &cImageDebugger::mnuExit_Click);

		mnuFile->DropDownItems->Add(mnuOpen);
		mnuFile->DropDownItems->Add(mnuExit);
	
		mnuMain->Items->Add(mnuFile);

		mnuHelp = gcnew ToolStripMenuItem(L"Help");
		mnuAbout = gcnew ToolStripMenuItem(L"About");
		mnuAbout->Click += gcnew System::EventHandler(this, &cImageDebugger::mnuAbout_Click);

		mnuHelp->DropDownItems->Add(mnuAbout);
		
		mnuMain->Items->Add(mnuHelp);

		aboutDialog = gcnew cAboutDialog();
		aboutDialog->App = this;

		Controls->Add(mnuMain);
		MainMenuStrip = mnuMain;	

		// tab control
		tabControl = gcnew TabControl();
	
		tabControl->ShowToolTips = true;
		tabControl->Location = System::Drawing::Point(0, 29);
		tabControl->Name = L"tabControl1";
		tabControl->SizeMode = TabSizeMode::Fixed;
		tabControl->SelectedIndex = 0;
		tabControl->Size = *tabSize;
		tabControl->TabIndex = 1;

		tabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &cImageDebugger::tabButton_Click);

		Controls->Add(tabControl);

		// file dialog
		ofd = gcnew OpenFileDialog;

		ofd->Multiselect = true;

		ofd->Filter = L"XML Files (*.xml)|*.xml|"
					  L"JPEG Files (*.jpg)|*.jpg|"
	                  L"PNG Files (*.png)|*.png|"	                  
					  L"GIF Files (*.gif)|*.gif|"
					  L"TIFF Files (*.tif)|*.tif";

		ofd->FilterIndex = 1;

		// flow layout
		flowLayoutPanel1 = gcnew FlowLayoutPanel();

		flowLayoutPanel1->Location = System::Drawing::Point(0, 32);
		flowLayoutPanel1->Name = L"flowLayoutPanel1";
		flowLayoutPanel1->Size = System::Drawing::Size(220, 600);
		flowLayoutPanel1->TabIndex = 1;
		
		Controls->Add(flowLayoutPanel1);

		flowLayoutPanel2 = gcnew FlowLayoutPanel();
		flowLayoutPanel2->Location = System::Drawing::Point(220, 32);
		flowLayoutPanel2->Name = L"flowLayoutPanel2";
		flowLayoutPanel2->Size = *tabSize;
		flowLayoutPanel2->TabIndex = 2;

		flowLayoutPanel2->Controls->Add(tabControl);
		Controls->Add(flowLayoutPanel2);

		locationInfo = gcnew cLocationInfo;
		locationInfo->LocationChanged += 
			gcnew LocationChangedEventHandler(this, &cImageDebugger::LocationChanged_Event);
	
		flowLayoutPanel1->Controls->Add(locationInfo);

		pixelInfo = gcnew cPixelInfo;

		margin = gcnew System::Drawing::Size();

		margin->Width = Size.Width - DEFAULT_CANVAS_WIDTH;
		margin->Height = Size.Height - DEFAULT_CANVAS_HEIGHT;

    }

protected:

	MenuStrip ^mnuMain;
	ToolStripMenuItem ^mnuFile;
	ToolStripMenuItem ^mnuOpen;
	ToolStripMenuItem ^mnuExit;

	ToolStripMenuItem ^mnuHelp;
	ToolStripMenuItem ^mnuAbout;

	FlowLayoutPanel ^flowLayoutPanel1;
	FlowLayoutPanel ^flowLayoutPanel2;

	TabControl ^tabControl;
	TabPage ^tpImage;

	OpenFileDialog ^ofd;

	cPixelInfo ^pixelInfo; 

	System::Drawing::Size ^margin, ^tabSize;

	cLocationInfo ^locationInfo;
	cAboutDialog ^aboutDialog;

protected:

	TabPage ^CreateImageAssets(int fileType, String ^fullFileName, String ^fileName) {

		// create a picturetab from the specified file
		cPictureTab ^pictureTab;
		
		if(fileType == 1) {

			pictureTab = gcnew cXmlPictureTab(fullFileName, tabSize);

		} else {

			pictureTab = gcnew cBytePictureTab(fullFileName, tabSize);
		}
	
		pictureTab->Location = System::Drawing::Point(4, 25);
	
		pictureTab->MouseOverPixel += 
			gcnew MouseOverPixelEventHandler(this, &cImageDebugger::MouseOverPixel_Event);
		
		pictureTab->CloseTab += 
			gcnew CloseTabEventHandler(this, &cImageDebugger::tabClose_Event);

		tabControl->Size = pictureTab->GetImageSize();		
		
		tabControl->TabPages->Add(pictureTab);
		tabControl->SelectedTab = pictureTab;

		// add a rgbainfo control for this picture tab
		cRGBAInfo ^rgbaInfo = gcnew cRGBAInfo(fileName, pictureTab->Name);
		flowLayoutPanel1->Controls->Add(rgbaInfo);
		
		locationInfo->EnableMode(true);
		
		return(tpImage);
	}

	void tabButton_Click(System::Object ^sender, System::EventArgs ^e)
	{
		int selectedIndex = tabControl->SelectedIndex;

		if(selectedIndex < 0) return;

	}

	void tabClose_Event(System::Object ^sender)
	{
		// close tab page and associated controls
		cPictureTab ^pictureTab = static_cast<cPictureTab ^>(sender);

		cli::array<Control ^> ^result;

		result = flowLayoutPanel1->Controls->Find(pictureTab->Name, true);

		flowLayoutPanel1->Controls->Remove(result[0]);

		tabControl->TabPages->Remove(pictureTab);

		if(tabControl->TabCount == 0) {

			locationInfo->EnableMode(false);
		}
	}

	void mnuOpen_Click(System::Object ^sender, System::EventArgs ^e)
	{
		if( ofd->ShowDialog() == ::DialogResult::OK  )
		{
			// allow opening of multiple files of the same type
			for(int i = 0; i < ofd->FileNames->Length; i++) {
				
				CreateImageAssets(ofd->FilterIndex, ofd->FileNames[i], ofd->SafeFileNames[i]);
			}

		}

	}

	void mnuExit_Click(System::Object ^sender, System::EventArgs ^e)
	{
		Close();
	}

	void mnuAbout_Click(System::Object ^sender, System::EventArgs ^e)
	{
		aboutDialog->ShowDialog();
	}

	void MouseOverPixel_Event(Object ^sender, Point ^mousePos) 
	{

		cPictureTab ^selectedPictureTab = static_cast<cPictureTab ^>(sender);

		for(int i = 0; i < tabControl->TabCount; i++) {

			// collect pixel values of all open tabs and display them in their
			// associated rgbainfo controls
			cPictureTab ^pictureTab = 
				static_cast<cPictureTab ^>(tabControl->TabPages->default[i]);

			pictureTab->GetPixelInfo(*mousePos, pixelInfo);

			cli::array<Control ^> ^result;

			result = flowLayoutPanel1->Controls->Find(pictureTab->Name, true);

			cRGBAInfo ^rgbaInfo = static_cast<cRGBAInfo ^>(result[0]);

			rgbaInfo->SetRGBAValues(pixelInfo);
		
			if(pictureTab == selectedPictureTab) {

				rgbaInfo->SetBackColor(Color::Aquamarine);

				locationInfo->SetLocation(mousePos);		
				locationInfo->SetZoomFactor(pictureTab->GetZoomFactor());

			} else {

				rgbaInfo->SetBackColor(Color::Transparent);
			}

		}
	}

	void LocationChanged_Event(Object ^sender, Point ^pos) {

		// modify the image source rectangle location and redraw the currently
		// selected picturetab
		cPictureTab ^pictureTab = 
			static_cast<cPictureTab ^>(tabControl->TabPages->default[tabControl->SelectedIndex]);

		pictureTab->SetImageSourceRectPos(*pos);
		pictureTab->Focus();

	}


};
