// clr test2.cpp : main project file.

#include "stdafx.h"
#include "image_debugger.h"


[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	//Application::Run(gcnew Form1());
	//Application::Run(gcnew Form1());
	Application::Run(gcnew cImageDebugger());
	return 0;
}
