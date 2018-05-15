#pragma once
#include"..\\Plex_lab\Classes.h"

namespace Plex_GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PlexGUI
	/// </summary>
	public ref class PlexGUI : public System::Windows::Forms::Form
	{
	public:
		
		TChart*pFirst;
		bool flag = false;
		TPoint*p1, *p2;
		int x1, y1, x2, y2;
		Graphics^gr;
		
		PlexGUI(void)
		{
			InitializeComponent();
			gr = CreateGraphics();
			pFirst = nullptr;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlexGUI()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->SuspendLayout();
			// 
			// PlexGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(873, 494);
			this->Name = L"PlexGUI";
			this->Text = L"PlexGUI";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::PlexGUI_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::PlexGUI_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::PlexGUI_MouseUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void PlexGUI_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		flag = true;
		x1 = x2 = e->X;
		y1 = y2 = e->Y;
	}
	private: System::Void PlexGUI_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (flag == true)
		{
			gr->DrawLine(Pens::White, x1, y1, x2, y2);
			x2 = e->X;
			y2 = e->Y;
			gr->DrawLine(Pens::Black, x1, y1, x2, y2);
		}
	}
	private: System::Void PlexGUI_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		flag = false;
		bool FindB = false, FindE = false;

		if (pFirst == nullptr)
		{
			p1 = new TPoint(x1, y1);
			p2 = new TPoint(x2, y2);
			pFirst = new TChart();
			pFirst->SetBegin(p1);
			pFirst->SetEnd(p2);
		}
		else
		{
			FindB = pFirst->Find(x1, y1);
			if(FindB)
			{
				p2 = new TPoint(x2, y2);
				if (pFirst->IsFirst())
					p1 = (TPoint*)pFirst->pRes->GetBegin();
				else
					p1 = (TPoint*)pFirst->pRes->GetEnd();
				TChart*tmp = new TChart();
				tmp->SetBegin(p2);
				tmp->SetEnd(p1);
				if (pFirst->IsFirst())
					pFirst->pRes->SetBegin(tmp);
				else
					pFirst->pRes->SetEnd(tmp);
			}

			FindE = pFirst->Find(x2, y2);
			if (FindE)
			{
				p2 = new TPoint(x1, y1);
				if (pFirst->IsFirst())
					p1 = (TPoint*)pFirst->pRes->GetBegin();
				else
					p1 = (TPoint*)pFirst->pRes->GetEnd();
				TChart*tmp = new TChart();
				tmp->SetBegin(p2);
				tmp->SetEnd(p1);
				if (pFirst->IsFirst())
					pFirst->pRes->SetBegin(tmp);
				else
					pFirst->pRes->SetEnd(tmp);
			}
			if(FindB == false && FindE == false) gr->DrawLine(Pens::White, x1, y1, x2, y2);
		}
	}
	};
}
