#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


public ref class cAboutDialog : public System::Windows::Forms::Form
{
public:

	cAboutDialog(void)
	{
		InitializeComponent();

	}

	Form ^App;

protected:

	~cAboutDialog()
	{
		if (components)
		{
			delete components;
		}
	}

protected: 

	System::Windows::Forms::Label^  label1;
	System::Windows::Forms::LinkLabel^  linkLabel1;
	System::Windows::Forms::Button^  okButton;
	String ^link;

private:

	System::ComponentModel::Container ^components;

	void InitializeComponent(void)
	{
		label1 = (gcnew System::Windows::Forms::Label());
		okButton = (gcnew System::Windows::Forms::Button());
		linkLabel1 = gcnew LinkLabel();
		
		// 
		// label1
		// 
		label1->AutoSize = true;
		label1->Location = System::Drawing::Point(80, 10);
		label1->Name = L"label1";
		label1->Size = System::Drawing::Size(67, 17);
		label1->TabIndex = 1;
		label1->Text = L"Image Debugger 0.5";
		// 
		// linkLabel1
		// 
		link = gcnew String(L"http://github.com/ijc123/Image-Debugger/");

		linkLabel1->AutoSize = true;
		linkLabel1->Location = System::Drawing::Point(15, 35);
		linkLabel1->Name = L"linkLabel1";
		linkLabel1->Size = System::Drawing::Size(67, 17);
		linkLabel1->TabIndex = 2;
		linkLabel1->Text = link;
		linkLabel1->LinkClicked += gcnew LinkLabelLinkClickedEventHandler(this, &cAboutDialog::LinkLabel1_LinkClicked);

		// 
		// okButton
		// 
		okButton->Location = System::Drawing::Point(99, 68);
		okButton->Name = L"okButton";
		okButton->Size = System::Drawing::Size(99, 28);
		okButton->TabIndex = 2;
		okButton->Text = L"Ok";
		okButton->UseVisualStyleBackColor = true;
		okButton->Click += gcnew EventHandler(this, &cAboutDialog::Button1_Click);
		// 
		// cAboutDialog
		// 
		StartPosition = FormStartPosition::CenterScreen;
		FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		MinimizeBox = false;
        MaximizeBox = false;
		AutoScaleDimensions = System::Drawing::SizeF(8, 16);
		AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		ClientSize = System::Drawing::Size(292, 125);
		Controls->Add(okButton);
		Controls->Add(label1);
		Controls->Add(linkLabel1);
		Name = L"cAboutDialog";
		Text = L"";
		AcceptButton = okButton;
	
	}

protected:

	void LinkLabel1_LinkClicked(System::Object ^sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs ^e)
    {
		System::Diagnostics::Process::Start(link);
		DialogResult = Windows::Forms::DialogResult::OK;
		App->WindowState = FormWindowState::Minimized;
	
		Close();
    }


	void Button1_Click(System::Object^  sender, System::EventArgs ^e) {

		DialogResult = Windows::Forms::DialogResult::OK;
		Close();
	}

};


