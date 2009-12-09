#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace clrtest2 {

	/// <summary>
	/// Summary for testform
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class testform : public System::Windows::Forms::Form
	{
	public:
		testform(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~testform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox1;
	protected: 
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox2;
	private: System::Windows::Forms::Label^  label1;


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
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox2 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->Cursor = System::Windows::Forms::Cursors::Default;
			this->maskedTextBox1->Location = System::Drawing::Point(12, 12);
			this->maskedTextBox1->Mask = L"00000000";
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->Size = System::Drawing::Size(68, 22);
			this->maskedTextBox1->TabIndex = 0;
			// 
			// maskedTextBox2
			// 
			this->maskedTextBox2->Location = System::Drawing::Point(86, 12);
			this->maskedTextBox2->Margin = System::Windows::Forms::Padding(4, 3, 3, 3);
			this->maskedTextBox2->Name = L"maskedTextBox2";
			this->maskedTextBox2->Size = System::Drawing::Size(72, 22);
			this->maskedTextBox2->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(175, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// testform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 265);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->maskedTextBox2);
			this->Controls->Add(this->maskedTextBox1);
			this->Name = L"testform";
			this->Text = L"testform";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
