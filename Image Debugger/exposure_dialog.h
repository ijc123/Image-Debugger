#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for cExposureDialog
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class cExposureDialog : public System::Windows::Forms::Form
{
public:

	cExposureDialog(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
	}

	float exposure;

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~cExposureDialog()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
protected: 
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Button^  button1;

protected: 

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		
		numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
		label1 = (gcnew System::Windows::Forms::Label());
		button1 = (gcnew System::Windows::Forms::Button());
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
		// button1
		// 
		button1->Location = System::Drawing::Point(99, 68);
		button1->Name = L"button1";
		button1->Size = System::Drawing::Size(99, 28);
		button1->TabIndex = 2;
		button1->Text = L"Ok";
		button1->UseVisualStyleBackColor = true;
		button1->Click += gcnew EventHandler(this, &cExposureDialog::button1_Click);
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
		Controls->Add(button1);
		Controls->Add(label1);
		Controls->Add(numericUpDown1);
		Name = L"cExposureDialog";
		Text = L"";
		Load += gcnew System::EventHandler(this, &cExposureDialog::Form1_Load);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(numericUpDown1))->EndInit();
		AcceptButton = button1;
		ResumeLayout(false);
		PerformLayout();
	
	}
#pragma endregion
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 numericUpDown1->Value = Convert::ToDecimal(exposure);
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: void button1_Click(System::Object^  sender, System::EventArgs ^e) {

			 exposure = Convert::ToSingle(numericUpDown1->Value);
			 DialogResult = Windows::Forms::DialogResult::OK;
			 Close();
		 }
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

			
		 }
};


