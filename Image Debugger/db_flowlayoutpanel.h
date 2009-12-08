#pragma once
#using <System.dll>
#using <System.Xml.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;

// double buffered flow layout panel
public ref class cDBFlowLayoutPanel : public FlowLayoutPanel
{

public:

	cDBFlowLayoutPanel() 
    {		

		DoubleBuffered = true;

    }


protected:



};
