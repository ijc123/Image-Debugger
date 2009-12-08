#pragma once
#include "picture_tab.h"
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;


public ref class cIntPictureTab : public cPictureTab
{

public:

	cIntPictureTab(String ^fileName) :
		cPictureTab(fileName)
    {		
		

    }

	virtual void GetPixelInfo(Point pos, PixelInfo ^info) override {

		if(pos.X < 0 || pos.X >= bitmap->Width || pos.Y < 0 || pos.Y >= bitmap->Height) {

			info->R = 0;
			info->G = 0;
			info->B = 0;
			info->A = 0;

			return;
		}

		Color color = bitmap->GetPixel(pos.X, pos.Y);

		info->R = float(color.R);
		info->G = float(color.G);
		info->B = float(color.B);
		info->A = float(color.A);

	}


protected:

	virtual void LoadImage(String ^fileName) override {

		bitmap = gcnew Bitmap(fileName);	
	}


};
