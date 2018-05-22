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
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  button1;
	public:
		Graphics^gr;
		
		PlexGUI(void)
		{
			InitializeComponent();
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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(13, 13);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(756, 469);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::pictureBox1_MouseClick);
			this->pictureBox1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::pictureBox1_MouseDoubleClick);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &PlexGUI::pictureBox1_MouseUp);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(776, 28);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(67, 17);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->Text = L"Highlight";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(776, 52);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Delete";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &PlexGUI::button1_Click);
			// 
			// PlexGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(936, 494);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"PlexGUI";
			this->Text = L"PlexGUI";
			this->Load += gcnew System::EventHandler(this, &PlexGUI::PlexGUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void PlexGUI_Load(System::Object^  sender, System::EventArgs^  e) {
		gr = pictureBox1->CreateGraphics();
	}
private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	flag = true;
	x1 = x2 = e->X;
	y1 = y2 = e->Y;
}
private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (flag == true)
	{
		if(pFirst) pFirst->Show(gr);
		gr->DrawLine(Pens::White, x1, y1, x2, y2);
		x2 = e->X;
		y2 = e->Y;
		gr->DrawLine(Pens::Black, x1, y1, x2, y2);
	}
}
private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	flag = false;
	if (!checkBox1->Checked)
	{
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
			if (FindB)
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
			if (FindB == false && FindE == false) gr->DrawLine(Pens::White, x1, y1, x2, y2);
		}
		pFirst->Show(gr);
	}
}
private: System::Void pictureBox1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (checkBox1->Checked)
	{
		x1 = x2 = e->X;
		y1 = y2 = e->Y;
		pFirst->Highlite(gr, x1, y1);
	}
}
private: System::Void pictureBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

}
};
}
