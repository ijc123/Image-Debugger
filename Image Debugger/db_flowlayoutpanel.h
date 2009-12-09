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


public ref class cDBFlowLayoutPanel : public FlowLayoutPanel
{

public:

	cDBFlowLayoutPanel() 
    {		
		// for some reason the doublebuffered property for a flowlayourpanel 
		// cannot be set from outside the class
		DoubleBuffered = true;

    }


protected:



};
