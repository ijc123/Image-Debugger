#pragma once
#include "db_flowlayoutpanel.h"

#define DEFAULT_CANVAS_WIDTH	1024
#define DEFAULT_CANVAS_HEIGHT	768

#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

public ref class PixelInfo 
{
public:

	float R,G,B,A;

};

public delegate void MouseOverPixelEventHandler(Object ^sender, Point ^pos);
public delegate void CloseTabEventHandler(Object ^sender);


public ref class cPictureTab abstract : public TabPage
{

public:

	event MouseOverPixelEventHandler ^MouseOverPixel {

		void add(MouseOverPixelEventHandler ^d) {

			mouseOverPixelEvent += d;

		}
		void remove(MouseOverPixelEventHandler ^d) {

			mouseOverPixelEvent -= d;
		}
		void raise(Object ^sender, Point ^pos) {

			if(mouseOverPixelEvent) {

				mouseOverPixelEvent->Invoke(sender, pos);

			}
		}
	}

	event CloseTabEventHandler ^CloseTab {

		void add(CloseTabEventHandler ^d) {

			closeEvent += d;

		}
		void remove(CloseTabEventHandler ^d) {

			closeEvent -= d;
		}
		void raise(Object ^sender) {

			if(closeEvent) {

				closeEvent->Invoke(sender);
			}
		}
	}

	virtual void GetPixelInfo(Point pos, PixelInfo ^info) abstract;


	System::Drawing::Size GetImageSize(void) {

		System::Drawing::Size imageSize(bitmap->Width, bitmap->Height);

		return(imageSize);

	}

	Point ZoomedPos(Point pos) {

		Point zoomedPos;

		// add 0.5 to the position to properly align the mouse cursor
		// with the pixels on screen
		zoomedPos.X = imageSourceRect.X + (pos.X + zoomFactor / 2) / zoomFactor;
		zoomedPos.Y = imageSourceRect.Y + (pos.Y + zoomFactor / 2) / zoomFactor;

		return(zoomedPos);
	}


protected:

	cPictureTab(String ^fileName)
	{		
		globalFlip = false;
		localFlip = false;
		first = true;
		zoomFactor = 1;

		LoadImage(fileName);

		imageSourceRect = Rectangle(0,0,DEFAULT_CANVAS_WIDTH,DEFAULT_CANVAS_HEIGHT);

		Name = id.ToString();
		id++;
		Text = fileName;
		ToolTipText = fileName;
		
		panel = gcnew cDBFlowLayoutPanel();
		panel->Size = System::Drawing::Size(DEFAULT_CANVAS_WIDTH,DEFAULT_CANVAS_HEIGHT);	
		panel->MinimumSize = System::Drawing::Size(DEFAULT_CANVAS_WIDTH,DEFAULT_CANVAS_HEIGHT);	
		panel->MaximumSize = System::Drawing::Size(DEFAULT_CANVAS_WIDTH,DEFAULT_CANVAS_HEIGHT);
		panel->Dock = DockStyle::Fill;
		panel->AutoSize = true;
		panel->Cursor = Cursors::Cross;
		panel->AutoScroll = true;
		panel->MouseMove += gcnew MouseEventHandler(this, &cPictureTab::MouseMove_Event);
		panel->MouseUp += gcnew MouseEventHandler(this, &cPictureTab::MouseUp_Event);
		panel->MouseClick += gcnew MouseEventHandler(this, &cPictureTab::MouseWheel_Event);
		//panel->MouseWheel += gcnew MouseEventHandler(this, &cPictureTab::MouseWheel_Event);
		panel->Paint += gcnew PaintEventHandler(this, &cPictureTab::Panel_OnPaint);	
		
		Controls->Add(panel);
			
		mousePos = gcnew Point();

		System::Windows::Forms::ContextMenuStrip ^context =
			gcnew System::Windows::Forms::ContextMenuStrip;

		ToolStripMenuItem ^mnuClose = gcnew ToolStripMenuItem(L"Close");
		mnuClose->Click += gcnew EventHandler(this, &cPictureTab::mnuClose_Click);

		context->Items->Add(mnuClose);

		ToolStripMenuItem ^mnuFlip = gcnew ToolStripMenuItem(L"Flip");
		mnuFlip->Click += gcnew EventHandler(this, &cPictureTab::mnuFlip_Click);

		context->Items->Add(mnuFlip);

		ToolStripMenuItem ^mnuUnZoom = gcnew ToolStripMenuItem(L"UnZoom");
		mnuUnZoom->Click += gcnew EventHandler(this, &cPictureTab::mnuUnZoom_Click);

		context->Items->Add(mnuUnZoom);

		ContextMenuStrip = context;


	}

	virtual void LoadImage(String ^fileName) abstract;

	void MouseMove_Event(Object ^sender, MouseEventArgs ^e)
	{
		mousePos = ZoomedPos(Point(e->X, e->Y));

		if(e->Button == System::Windows::Forms::MouseButtons::Middle) {

			if(first) {
				
				prevMousePos.X = e->X;
				prevMousePos.Y = e->Y;
				first = false;
			}

			imageSourceRect.X += e->X - prevMousePos.X;
			imageSourceRect.Y += e->Y - prevMousePos.Y;

			prevMousePos.X = e->X;
			prevMousePos.Y = e->Y;

			panel->Cursor = System::Windows::Forms::Cursors::Hand;
			panel->Refresh();
		}

		MouseOverPixel(this, mousePos);
		
	}

	void MouseUp_Event(Object ^sender, MouseEventArgs ^e)
	{

		first = true;
		panel->Cursor = System::Windows::Forms::Cursors::Cross;
	}

	void MouseWheel_Event(Object ^sender, MouseEventArgs ^e)
	{

		if(e->Button != System::Windows::Forms::MouseButtons::Left) return; 

		Point screenPos = ZoomedPos(Point(e->X, e->Y));

		//if(e->Delta > 0) {
			
			zoomFactor *= 2;
/*
		} else {

			if(zoomFactor > 1) {

				zoomFactor /= 2;
			}
		}
*/
		
		imageSourceRect.Width = DEFAULT_CANVAS_WIDTH / zoomFactor;
		imageSourceRect.Height = DEFAULT_CANVAS_HEIGHT / zoomFactor;

		imageSourceRect.X = screenPos.X - imageSourceRect.Width / 2;
		imageSourceRect.Y = screenPos.Y - imageSourceRect.Height / 2;

		panel->Refresh();
		
	}


	void mnuClose_Click(Object ^sender, EventArgs ^e)
	{	
		CloseTab(this);
	}

	void mnuFlip_Click(Object ^sender, EventArgs ^e)
	{	
		if(globalFlip == true) globalFlip = false;
		else globalFlip = true;
		
		panel->Refresh();
	}

	void mnuUnZoom_Click(Object ^sender, EventArgs ^e)
	{	
		
		zoomFactor = 1;
		imageSourceRect = Rectangle(0,0,DEFAULT_CANVAS_WIDTH,DEFAULT_CANVAS_HEIGHT);
		panel->Refresh();

	}

	void Panel_OnPaint(Object ^Sender, PaintEventArgs ^e) {

		Graphics ^gPanel = e->Graphics;
		gPanel->InterpolationMode = Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
				
		if(localFlip != globalFlip) {
			
			bitmap->RotateFlip(RotateFlipType::RotateNoneFlipY);
			localFlip = globalFlip;
		}

		gPanel->DrawImage(bitmap, Rectangle(0,0,DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT),
			imageSourceRect, GraphicsUnit::Pixel);	
		
	}

	cDBFlowLayoutPanel ^panel;
	Bitmap ^bitmap;
	Point ^mousePos;

	static Rectangle imageSourceRect;
	static int zoomFactor;

	static bool globalFlip;
	bool localFlip;

	static Point prevMousePos;
	static bool first;

	static int id = 0;

	MouseOverPixelEventHandler ^mouseOverPixelEvent;
	CloseTabEventHandler ^closeEvent;

};
