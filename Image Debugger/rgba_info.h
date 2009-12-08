#pragma once
#include "picture_tab.h"

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class cRGBAInfo : public FlowLayoutPanel {

public:

	cRGBAInfo(String ^FileName, String ^id)
    {
				
		Margin = System::Windows::Forms::Padding(0);
		Size = System::Drawing::Size(226, 44);	
		Name = id;

		lblFileName = gcnew Label();
		lblFileName->AutoSize = true;
		lblFileName->Margin = System::Windows::Forms::Padding(0);
		lblFileName->Location = System::Drawing::Point(0, 0);
		lblFileName->MaximumSize = System::Drawing::Size(223, 17);
		lblFileName->MinimumSize = System::Drawing::Size(223, 17);
		lblFileName->Size = System::Drawing::Size(223, 17);
		lblFileName->Text = FileName;

		Controls->Add(lblFileName);

		R = gcnew Label();
		R->AutoSize = true;
		R->Margin = System::Windows::Forms::Padding(0);
		R->ForeColor = Color::Red;
		R->Location = System::Drawing::Point(0, 17);
		R->MaximumSize = System::Drawing::Size(55, 17);
		R->MinimumSize = System::Drawing::Size(55, 17);
		R->Size = System::Drawing::Size(46, 17);
		
		Controls->Add(R);

		G = gcnew Label();
		G->AutoSize = true;
		G->Margin = System::Windows::Forms::Padding(0);
		G->ForeColor = Color::Green;
		G->Location = System::Drawing::Point(55, 17);
		G->MaximumSize = System::Drawing::Size(55, 17);
		G->MinimumSize = System::Drawing::Size(55, 17);
		G->Size = System::Drawing::Size(46, 17);

		Controls->Add(G);

		B = gcnew Label();
		B->AutoSize = true;
		B->Margin = System::Windows::Forms::Padding(0);
		B->ForeColor = Color::Blue;
		B->Location = System::Drawing::Point(110, 17);
		B->MaximumSize = System::Drawing::Size(55, 17);
		B->MinimumSize = System::Drawing::Size(55, 17);
		B->Size = System::Drawing::Size(46, 17);

		Controls->Add(B);

		A = gcnew Label();
		A->AutoSize = true;
		A->Margin = System::Windows::Forms::Padding(0);
		A->ForeColor = Color::Gray;
		A->Location = System::Drawing::Point(165, 17);
		A->MaximumSize = System::Drawing::Size(55, 17);
		A->MinimumSize = System::Drawing::Size(55, 17);
		A->Size = System::Drawing::Size(46, 17);
		
		Controls->Add(A);

		float init = 0;

		R->Text = init.ToString();
		G->Text = init.ToString();
		B->Text = init.ToString();
		A->Text = init.ToString();
    }

	void SetRGBAValues(PixelInfo ^pixelInfo) {

		R->Text = pixelInfo->R.ToString();
		G->Text = pixelInfo->G.ToString();
		B->Text = pixelInfo->B.ToString();
		A->Text = pixelInfo->A.ToString();

	}

	void SetBackColor(Color color) {

		lblFileName->BackColor = color;
		R->BackColor = color;
		G->BackColor = color;
		B->BackColor = color;
		A->BackColor = color;

	}

protected:

	Label ^lblFileName;
	Label ^R, ^G, ^B, ^A;

};