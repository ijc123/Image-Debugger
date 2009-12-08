#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// dialog to modify exposure values of XML images, exposure values
// are stored on a per image basis
public ref class cExposureDialog : public System::Windows::Forms::Form
{
public:

	cExposureDialog(void)
	{
		InitializeComponent();

	}

	float exposure;

protected:

	~cExposureDialog()
	{
		if (components)
		{
			delete components;
		}
	}

protected: 

	System::Windows::Forms::NumericUpDown^  numericUpDown1;

	System::Windows::Forms::Label^  label1;
	System::Windows::Forms::Button^  okButton;

private:

	System::ComponentModel::Container ^components;

	void InitializeComponent(void)
	{		
		numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
		label1 = (gcnew System::Windows::Forms::Label());
		okButton = (gcnew System::Windows::Forms::Button());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(numericUpDown1))->BeginInit();
		SuspendLayout();
		// 
		// numericUpDown1
		// 
		numericUpDown1->Location = System::Drawing::Point(12, 12);
		numericUpDown1->Name = L"numericUpDown1";
		numericUpDown1->Size = System::Drawing::Size(100, 22);
		numericUpDown1->TabIndex = 0;
		numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &cExposureDialog::numericUpDown1_ValueChanged);
		numericUpDown1->Minimum = Convert::ToDecimal(-1000);
		numericUpDown1->Maximum = Convert::ToDecimal(0);
		numericUpDown1->Increment = Convert::ToDecimal(0.25);
		numericUpDown1->DecimalPlaces = 2;
		// 
		// label1
		// 
		label1->AutoSize = true;
		label1->Location = System::Drawing::Point(118, 14);
		label1->Name = L"label1";
		label1->Size = System::Drawing::Size(67, 17);
		label1->TabIndex = 1;
		label1->Text = L"Exposure";
		// 
		// okButton
		// 
		okButton->Location = System::Drawing::Point(99, 68);
		okButton->Name = L"okButton";
		okButton->Size = System::Drawing::Size(99, 28);
		okButton->TabIndex = 2;
		okButton->Text = L"Ok";
		okButton->UseVisualStyleBackColor = true;
		okButton->Click += gcnew EventHandler(this, &cExposureDialog::button1_Click);
		// 
		// cExposureDialog
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
		Controls->Add(numericUpDown1);
		Name = L"cExposureDialog";
		Text = L"";
		Load += gcnew System::EventHandler(this, &cExposureDialog::Form1_Load);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(numericUpDown1))->EndInit();
		AcceptButton = okButton;
		ResumeLayout(false);
		PerformLayout();
	
	}

protected:

	void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

		numericUpDown1->Value = Convert::ToDecimal(exposure);
	}

	void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	void button1_Click(System::Object^  sender, System::EventArgs ^e) {

		exposure = Convert::ToSingle(numericUpDown1->Value);
		DialogResult = Windows::Forms::DialogResult::OK;
		Close();
	}

	void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {


	}
};


