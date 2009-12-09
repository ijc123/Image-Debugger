#pragma once
#include "picture_tab.h"

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

//using namespace System::Runtime::InteropServices;
//[DllImport("user32.dll")]
//extern "C" bool HideCaret(IntPtr hWnd);

public delegate void LocationChangedEventHandler(Object ^sender, Point ^pos);

public ref class cLocationInfo : public FlowLayoutPanel {

public:

	event LocationChangedEventHandler ^LocationChanged {

		void add(LocationChangedEventHandler ^d) {

			LocationChangedEvent += d;

		}
		void remove(LocationChangedEventHandler ^d) {

			LocationChangedEvent -= d;
		}
		void raise(Object ^sender, Point ^pos) {

			if(LocationChangedEvent) {

				LocationChangedEvent->Invoke(sender, pos);

			}
		}
	}

	cLocationInfo(void)
    {
				
		Margin = System::Windows::Forms::Padding(3);
		Size = System::Drawing::Size(226, 17);	
		Name = L"LocationInfo";

		int init = 0;

		xPos = gcnew MaskedTextBox();
		xPos->AutoSize = true;
		xPos->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		xPos->Margin = System::Windows::Forms::Padding(0);
		xPos->Location = System::Drawing::Point(0, 0);
		xPos->MaximumSize = System::Drawing::Size(55, 17);
		xPos->MinimumSize = System::Drawing::Size(55, 17);
		xPos->Size = System::Drawing::Size(55, 17);
		xPos->Enabled = false;
		xPos->Text = init.ToString();
		xPos->KeyPress += gcnew KeyPressEventHandler(this, &cLocationInfo::EnterLocation_Event);
		//HideCaret(xPos->Handle);
	
		Controls->Add(xPos);

		yPos = gcnew MaskedTextBox();
		yPos->AutoSize = true;
		yPos->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
		yPos->Margin = System::Windows::Forms::Padding(0);
		yPos->Location = System::Drawing::Point(55, 0);
		yPos->MaximumSize = System::Drawing::Size(55, 17);
		yPos->MinimumSize = System::Drawing::Size(55, 17);
		yPos->Size = System::Drawing::Size(55, 17);
		yPos->Enabled = false;
		yPos->Text = init.ToString();
		yPos->KeyPress += gcnew KeyPressEventHandler(this, &cLocationInfo::EnterLocation_Event);
		//HideCaret(yPos->Handle);

		Controls->Add(yPos);

		lblZoomFactor = gcnew Label();
		lblZoomFactor->AutoSize = true;
		lblZoomFactor->Margin = System::Windows::Forms::Padding(10, 0, 0, 0);
		lblZoomFactor->Location = System::Drawing::Point(110, 0);
		lblZoomFactor->MaximumSize = System::Drawing::Size(100, 17);
		lblZoomFactor->MinimumSize = System::Drawing::Size(100, 17);
		lblZoomFactor->Size = System::Drawing::Size(100, 17);
		lblZoomFactor->Text = L"Zoom: 1x";

		Controls->Add(lblZoomFactor);

		location = gcnew Point();
	
    }
	void EnableMode(bool mode) {
		
		xPos->Enabled = mode;
		yPos->Enabled = mode;

	}

	void SetLocation(Point ^pos) {		

		xPos->Text = pos->X.ToString();
		yPos->Text = pos->Y.ToString();

	}

	void SetZoomFactor(int zoomFactor) {

		lblZoomFactor->Text = L"Zoom: " + zoomFactor.ToString() + L"x";
	}

protected:

	void EnterLocation_Event(Object ^sender, KeyPressEventArgs ^e) {

		if(e->KeyChar == (char)8) {

			// allow backspace

		} else if(e->KeyChar == (char)13) {

			// if enter was pressed invoke location changed event
			// with the new position
			location->X = Convert::ToInt32(xPos->Text);
			location->Y = Convert::ToInt32(yPos->Text);

			LocationChanged(this, location);
		
		} else if(!System::Char::IsDigit(e->KeyChar)) {

			// discard non-digit input
			e->Handled = true;
		}
	}

	MaskedTextBox ^xPos;
	MaskedTextBox ^yPos;

	Label ^lblZoomFactor;
	Point ^location;

	LocationChangedEventHandler ^LocationChangedEvent;


};