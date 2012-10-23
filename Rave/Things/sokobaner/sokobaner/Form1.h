#pragma once

#include "confa.h"
#include <iostream>
#include <fstream>

using namespace std;

ofstream log;

namespace sokobaner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		BufferedGraphics^ grafx;
		BufferedGraphicsContext^ context;
		System::Drawing::Pen ^ myPen;
		System::Drawing::SolidBrush ^ myBrush;

		int lastpoint;
		int moving;
		unsigned char ** mas;
		unsigned char ** wmas;
		unsigned char ** masx;
		int numX;
		int dd;
		int tt;
		int td;
		int numY;
		int sim;

		int px,py;
		int bcount;
		confa * startconf;
		confa *curconf;

		winpath * wp;
		conflist * memory;

	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	public: 
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button6;

	private: System::Windows::Forms::Button^  button1;


	public:	Form1(void)
			{
				InitializeComponent();
				//
				//TODO: Add the constructor code here
				//

				log.open("log.txt");

				context = BufferedGraphicsManager::Current;
				context->MaximumBuffer = System::Drawing::Size( this->Width + 1, this->Height + 1 );
				grafx = context->Allocate( this->CreateGraphics(), Rectangle(0,0,this->Width,this->Height) );
				this->SetStyle( ControlStyles::OptimizedDoubleBuffer, true );

				myPen = gcnew Pen(Color::Gray,2);			
				myBrush = gcnew SolidBrush(Color::Gray);
				startconf=NULL;
				curconf=NULL;
				init();
			}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
			log.close();
		}

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
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->BeginInit();
			this->SuspendLayout();
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDown1->Location = System::Drawing::Point(514, 12);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {25, 0, 0, 0});
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(48, 20);
			this->numericUpDown1->TabIndex = 0;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDown2->Location = System::Drawing::Point(514, 38);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {25, 0, 0, 0});
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(48, 20);
			this->numericUpDown2->TabIndex = 1;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(473, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"numX";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(473, 40);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"numY";
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(487, 64);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"reinit";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->BackColor = System::Drawing::Color::DarkGray;
			this->radioButton1->Checked = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->radioButton1->Location = System::Drawing::Point(12, 10);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(86, 22);
			this->radioButton1->TabIndex = 4;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"стены ";
			this->radioButton1->UseVisualStyleBackColor = false;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->BackColor = System::Drawing::Color::MediumPurple;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->radioButton2->Location = System::Drawing::Point(12, 33);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(86, 22);
			this->radioButton2->TabIndex = 4;
			this->radioButton2->Text = L"ящики ";
			this->radioButton2->UseVisualStyleBackColor = false;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->BackColor = System::Drawing::Color::YellowGreen;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->radioButton3->Location = System::Drawing::Point(12, 56);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(86, 22);
			this->radioButton3->TabIndex = 4;
			this->radioButton3->Text = L"цели  ";
			this->radioButton3->UseVisualStyleBackColor = false;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->BackColor = System::Drawing::Color::Firebrick;
			this->radioButton4->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->radioButton4->Location = System::Drawing::Point(12, 79);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(86, 22);
			this->radioButton4->TabIndex = 4;
			this->radioButton4->Text = L"старт ";
			this->radioButton4->UseVisualStyleBackColor = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 104);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(19, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"    ";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 120);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(86, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = L"sim";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			this->button2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::button2_KeyDown);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(12, 311);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(550, 104);
			this->textBox1->TabIndex = 7;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox1_KeyDown);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 149);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(86, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"solve";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button4->Location = System::Drawing::Point(510, 91);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(52, 23);
			this->button4->TabIndex = 9;
			this->button4->Text = L"save";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileName = L"file.txt";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"file.txt";
			// 
			// button5
			// 
			this->button5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button5->Location = System::Drawing::Point(510, 120);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(52, 23);
			this->button5->TabIndex = 9;
			this->button5->Text = L"load";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 189);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(16, 20);
			this->textBox2->TabIndex = 10;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox2_KeyDown);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(510, 149);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(52, 23);
			this->button6->TabIndex = 11;
			this->button6->Text = L"prep";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(574, 427);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->radioButton4);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->numericUpDown2);
			this->Controls->Add(this->numericUpDown1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	protected:
		virtual void OnPaint( PaintEventArgs^ e ) override
		{
			grafx->Render( e->Graphics );
		}


		void DrawToBuffer(Graphics ^ g)
		{
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
			myBrush->Color=SystemColors::Control;
			grafx->Graphics->FillRectangle( myBrush, 0, 0, this->Width, this->Height );		

			myPen->Color=Color::Black;
			myPen->Width=2;
			grafx->Graphics->DrawRectangle(myPen,tt,td,dd*numY,dd*numX);
			myPen->Width=1;

			for(int i=0;i<numX;i++)
			{
				for(int j=0;j<numY;j++)
				{
					if(mas[i][j]==0)			 grafx->Graphics->FillRectangle(Brushes::LightGray,j*dd+tt,i*dd+td,dd,dd);
					if((mas[i][j]&128)!=0)grafx->Graphics->FillRectangle(Brushes::DimGray,j*dd+tt,i*dd+td,dd,dd);
					if((mas[i][j]&64)!=0)grafx->Graphics->FillRectangle(Brushes::MediumPurple,j*dd+tt,i*dd+td,dd,dd);
					if((mas[i][j]&32)!=0)grafx->Graphics->FillRectangle(Brushes::YellowGreen,j*dd+tt,i*dd+td,dd,dd);
					if((mas[i][j]&96)==96)grafx->Graphics->FillRectangle(Brushes::MediumSeaGreen,j*dd+tt,i*dd+td,dd,dd);
					if((mas[i][j]&16)!=0)grafx->Graphics->FillEllipse(Brushes::Firebrick,j*dd+tt,i*dd+td,dd,dd);
					if(wmas[i][j]==1)grafx->Graphics->DrawLine(myPen,j*dd+tt,i*dd+td,j*dd+tt+dd,i*dd+td+dd);
					grafx->Graphics->DrawRectangle(myPen,j*dd+tt,i*dd+td,dd,dd);
				}
			}

			if(curconf!=NULL)
			{
				System::Drawing::Font^ drawFont = gcnew System::Drawing::Font( "Arial",16 );
				for(int i=0;i<curconf->bcount;i++)
				{
					grafx->Graphics->DrawString(i.ToString(),drawFont,Brushes::AntiqueWhite,curconf->y[i]*dd+5+tt,curconf->x[i]*dd+5+td);
				}
			}
		}

		void init()
		{			
			lastpoint = 0;
			moving = 0;
			tt = 150;
			td = 10;
			dd = 30;
			sim=0;

			numX = (int)numericUpDown1->Value;
			numY = (int)numericUpDown2->Value;

			mas = new unsigned char * [numY];
			for(int i=0;i<numX;i++)
			{	
				mas[i]=new unsigned char[numX];
				for(int j=0;j<numY;j++)
				{
					mas[i][j]=0;
				}
			}

			wmas = new unsigned char * [numY];
			for(int i=0;i<numX;i++)
			{	
				wmas[i]=new unsigned char[numX];
				for(int j=0;j<numY;j++)
				{
					wmas[i][j]=0;
				}
			}

			masx = new unsigned char * [numY];
			for(int i=0;i<numX;i++)
			{	
				masx[i]=new unsigned char[numX];
				for(int j=0;j<numY;j++)
				{
					masx[i][j]=0;
				}
			}
			

			DrawToBuffer( grafx->Graphics );
			grafx->Render( Graphics::FromHwnd( this->Handle ) );
		}

		bool kirpich(int x, int y)
		{
			if((x<0)||(x>=numX)||(y<0)||(y>=numY))return true;
			if((mas[x][y]&128)==128)return true;
			else return false;
		}

		void badplaces()
		{
			for(int i=0;i<numX;i++)
			{					
				for(int j=0;j<numY;j++)
				{
					wmas[i][j]=0;
				}
			}

			// найдём тупо углы
			for(int i=0;i<numX;i++)
			{					
				for(int j=0;j<numY;j++)
				{
					if(((kirpich(i-1,j))&&(kirpich(i-1,j-1))&&(kirpich(i,j-1)))||
						((kirpich(i-1,j))&&(kirpich(i-1,j+1))&&(kirpich(i,j+1)))||
						((kirpich(i+1,j))&&(kirpich(i+1,j+1))&&(kirpich(i,j+1)))||
						((kirpich(i+1,j))&&(kirpich(i+1,j-1))&&(kirpich(i,j-1))))
					{
						if((mas[i][j]&(128+32))==0)wmas[i][j]=1;
					}

				}
			}

			//заполнение wmas - массива гиблых мест и безвыходных положений
			for(int i=0;i<numX;i++)
			{
				int j=0;
				while(j<numY)
				{
					while((mas[i][j]&128)!=0) //найдём начало замкнутого участка
					{
						j++;
						if(j==numY)break;
					}
					if(j<numY)
					{
						int start = j;
						while((mas[i][j]&128)==0) //найдём конец замкнутого участка
						{
							j++;
							if(j==numY)break;
						}
						int finish = j-1;
						bool ans = true; //тупик
						for(int k=start;k<=finish;k++)
						{
							if(i-1<0) break; //слева от участка забор
							if((mas[i][k]&32)!=0)ans=false;//на участке есть цели
							if((mas[i-1][k]&128)==0)ans=false;//слева от участка есть проход
						}
						if(ans==false)
						{
							ans = true;
							for(int k=start;k<=finish;k++)
							{
								if(i+1==numX) break; //справа от участка забор							
								if((mas[i+1][k]&128)==0)ans=false;//справа от участка есть проход
							}
						}
						if(ans==true) //пометим замкнутый участок в спецмассиве.
						{
							for(int k=start;k<=finish;k++)
							{
								wmas[i][k]=1;							
							}
						}
					}
				}
			}

			for(int j=0;j<numY;j++)
			{
				int i=0;
				while(i<numX)
				{
					while((mas[i][j]&128)!=0) //найдём начало замкнутого участка
					{
						i++;
						if(i==numX)break;
					}
					if(i<numX)
					{
						int start = i;
						while((mas[i][j]&128)==0) //найдём конец замкнутого участка
						{
							i++;
							if(i==numX)break;
						}
						int finish = i-1;
						bool ans = true; //тупик
						for(int k=start;k<=finish;k++)
						{
							if(j-1<0) break; //слева от участка забор
							if((mas[k][j]&32)!=0)ans=false;//на участке есть цели
							if((mas[k][j-1]&128)==0)ans=false;//слева от участка есть проход
						}
						if(ans==false)
						{
							ans = true;
							for(int k=start;k<=finish;k++)
							{
								if(j+1==numY) break; //справа от участка забор							
								if((mas[k][j+1]&128)==0)ans=false;//справа от участка есть проход
							}
						}
						if(ans==true) //пометим замкнутый участок в спецмассиве.
						{
							for(int k=start;k<=finish;k++)
							{
								wmas[k][j]=1;							
							}
						}
					}
				}
			}
		}


		void prep()
		{
			for(int i=0;i<numX;i++)
			{
				for(int j=0;j<numY;j++)
				{
					if((mas[i][j]&16)!=0)
					{
						px=i;
						py=j;
					}
					//masx[i][j]=((mas[i][j])&(255-(64+16)));
				}
			}

			bcount = 0;
			for(int i=0;i<numX;i++)
			{
				for(int j=0;j<numY;j++)
				{
					if((mas[i][j]&64)!=0)
					{
						bcount++;
					}
				}
			}

			badplaces();

			startconf = new confa(mas,bcount,numX,numY);
			curconf = new confa(startconf);

		}

		bool checkwin()
		{
			for(int i=0;i<numX;i++)
			{
				for(int j=0;j<numY;j++)
				{
					if((mas[i][j]&32)!=0)
						if((mas[i][j]&64)==0)return false;
				}				
			}
			return true;
		}

		void play(int x, int y)
		{
			if((px+x<0)||(px+x>=numX)||(py+y<0)||(py+y>=numY))return;
			if((mas[px+x][py+y]&128)!=0)return;
			
			if((mas[px+x][py+y]&64)!=0)
			{
				if((px+x+x<0)||(px+x+x>=numX)||(py+y+y<0)||(py+y+y>=numY))return;
				if((mas[x+x+px][y+y+py]&(128+64))==0)
				{
					mas[x+x+px][y+y+py]=mas[x+x+px][y+y+py]|64;
					mas[x+px][y+py]=mas[x+px][y+py]|16;
					mas[x+px][y+py]=mas[x+px][y+py]&(255-64);
					mas[px][py]=mas[px][py]&(255-16);
					
					for(int i=0;i<curconf->bcount;i++)
						if((curconf->x[i]==px+x)&&(curconf->y[i]==py+y))
						{
							curconf->x[i]=px+x+x;
							curconf->y[i]=py+y+y;
						}		

					px=px+x;
					py=py+y;								
				}
			}
			else
			{
				mas[x+px][y+py]=mas[x+px][y+py]|16;
				mas[px][py]=mas[px][py]&(255-16);				
				px=px+x;
				py=py+y;				
			}

			if(checkwin())
			{
				label3->Text = "win";
				sim=0;
				button2->Text="sim off";
			}			

			DrawToBuffer( grafx->Graphics );
			grafx->Render( Graphics::FromHwnd( this->Handle ) );
		}

		//офигенно генияльноя проседура =)
		void RecSearch(confa * cf, path * p)
		{	
			/*pathnode * pn = p->tail;
			while(pn!=0)
			{
				char st[10];
				switch(pn->wh)
				{
					case 128:{strcpy(st,"up");break;}
					case 32:{strcpy(st,"down");break;}
					case 64:{strcpy(st,"left");break;}
					case 16:{strcpy(st,"right");break;}
				}
				log<<(int)pn->x<<"-"<<st<<" "<<endl;
				pn=pn->next;
			}*/

			if(p->length>wp->BestRes)return; //слишком долго! надоело

			if(memory->check(cf,p)){return;} //я помню! я тут уже был!
			
			memory->add(cf,p); //я запомню что уже тут был!

			/*for(int i=0;i<numX;i++)
			{
				for(int j=0;j<numY;j++)
				{
					if((mas[i][j]&128)!=0)log<<"#";
					else if((mas[i][j]&64)!=0)log<<"0";
					else if((mas[i][j]&1)!=0)log<<"1";
					else log<<2;
				}
				log<<endl;
			}
			log<<endl;
			log<<endl;
			*/
			if(cf->win())//бинго! я выйграл!
			{
				wp->add(p);//я это запомню	
				log<<"win!"<<endl;
				return;
			}
			if(cf->lose()){return;} //я проиграл :( пожалуй запоминать тут нечего

			//нахождение следующего решения методом Тупорылого Перебора
			for(int i=0;i<cf->bcount;i++)
			{								
				if(((cf->r[i])&(confa::LEFT))!=0)RecSearch(cf->move(i,confa::LEFT),new path(p,i,confa::LEFT));
				if(((cf->r[i])&(confa::RIGHT))!=0)RecSearch(cf->move(i,confa::RIGHT),new path(p,i,confa::RIGHT));
				if(((cf->r[i])&(confa::UP))!=0)RecSearch(cf->move(i,confa::UP),new path(p,i,confa::UP));
				if(((cf->r[i])&(confa::DOWN))!=0)RecSearch(cf->move(i,confa::DOWN),new path(p,i,confa::DOWN));
			}
		}
		void solve()
		{
			prep();
			wp = new winpath();
			memory = new conflist();
			path * p1 = new path();
			RecSearch(startconf,p1);
			
			label3->Text="Done!";

			if(wp->head!=NULL)
			{
				textBox1->Clear();
				path * p = wp->best();
				pathnode * pn = p->tail;
				while(pn!=0)
				{
					String ^ st;
					switch(pn->wh)
					{
						case 128:{st="вниз";break;}
						case 32:{st="вверх";break;}
						case 64:{st="вправо";break;}
						case 16:{st="влево";break;}
					}
					textBox1->Text=String::Concat(textBox1->Text,pn->x,"-",st," ");
					pn=pn->next;
				}
			}
			else
			textBox1->Text="Решений нет!";
			
			
			startconf->makemas();
			mas[px][py]=mas[px][py]|16;			
		}

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
			 {
				 DrawToBuffer( grafx->Graphics );
				 grafx->Render( Graphics::FromHwnd( this->Handle ) );
			 }
	private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
			 {
				 if((e->X<dd*numY+tt)&&(e->X>tt)&&(e->Y<dd*numX+td)&&(e->Y>td))
				 {
					 moving = 1;
					 int y1 = (e->X-tt)/dd;
					 int x1 = (e->Y-td)/dd;
					 lastpoint = y1*numY+x1;

					 if(e->Button==System::Windows::Forms::MouseButtons::Right)mas[x1][y1]=0;
					 else
					 {							 
						 if(radioButton1->Checked)mas[x1][y1]=mas[x1][y1]=128;
						 if((radioButton2->Checked)&&((mas[x1][y1]&(128+16))==0))mas[x1][y1]=mas[x1][y1]|64;
						 if((radioButton3->Checked)&&((mas[x1][y1]&(128))==0))mas[x1][y1]=mas[x1][y1]|32;
						 if(radioButton4->Checked)
						 {
							 if((mas[x1][y1]&192)==0)
							 {
								for(int i=0;i<numX;i++)
									for(int j=0;j<numY;j++) if(((mas[i][j])&16)!=0)mas[i][j]-=16;
								mas[x1][y1]=mas[x1][y1]|16;
								px=x1;
								py=y1;
							 }
						 }
					 }	

					 label3->Text=mas[x1][y1].ToString();

					 DrawToBuffer( grafx->Graphics );
					 grafx->Render( Graphics::FromHwnd( this->Handle ) );
				 }
			 }
	private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
			 {
				 if((e->X<dd*numY+tt)&&(e->X>tt)&&(e->Y<dd*numX+td)&&(e->Y>td)&&(moving==1))
				 {
					 int y1 = (e->X-tt)/dd;
					 int x1 = (e->Y-td)/dd;
					 if((y1*numX+x1)!=lastpoint)
					 {					 
						 lastpoint = y1*numX+x1;
						 if(e->Button==System::Windows::Forms::MouseButtons::Right)mas[x1][y1]=0;
						 else
						 {							 
							 if(radioButton1->Checked)mas[x1][y1]=mas[x1][y1]=128;
							 if((radioButton2->Checked)&&((mas[x1][y1]&(128+16))==0))mas[x1][y1]=mas[x1][y1]|64;
							 if((radioButton3->Checked)&&((mas[x1][y1]&(128))==0))mas[x1][y1]=mas[x1][y1]|32;
							 if(radioButton4->Checked)
							 {
								 if((mas[x1][y1]&192)==0)
								 {
									 for(int i=0;i<numX;i++)
										 for(int j=0;j<numY;j++) if(((mas[i][j])&16)!=0)mas[i][j]-=16;
									 mas[x1][y1]=mas[x1][y1]|16;
									 px=x1;
									 py=y1;
								 }
							 }
						 }	

						 label3->Text=mas[x1][y1].ToString();

						 DrawToBuffer( grafx->Graphics );
						 grafx->Render( Graphics::FromHwnd( this->Handle ) );
					 }
				 }
			 }
	private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
			 {
				 moving = 0;
			 }
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
			 {

			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 init();
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
			 {
				 		
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if(sim==0)
				 {
					 sim=1;
					 prep();
					 button2->Text="sim on";
				 }
				 else
				 {
					 sim=0;
					 button2->Text="sim off";
				 }
			 }
	private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
			 {
				 if(sim==1)
				 {
					 if(e->KeyData==Keys::A)	play(0,-1);
					 if(e->KeyData==Keys::D)	play(0,1);
					 if(e->KeyData==Keys::W)	play(-1,0);
					 if(e->KeyData==Keys::S)	play(1,0);
				 }	
			 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 solve();
			 DrawToBuffer( grafx->Graphics );
			 grafx->Render( Graphics::FromHwnd( this->Handle ) );
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
		 {			 
			 if(saveFileDialog1->ShowDialog()==System::Windows::Forms::DialogResult::OK)
			 {
		        System::IO::Stream ^ fs = saveFileDialog1->OpenFile();
				fs->WriteByte((char)numX);
				fs->WriteByte((char)numY);
				for(int i=0;i<numX;i++)
				{						
					for(int j=0;j<numY;j++)
					{
						fs->WriteByte(mas[i][j]);
					}
				}
				fs->Close();
			 }
		 }
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(openFileDialog1->ShowDialog()==System::Windows::Forms::DialogResult::OK)
			 {
		        System::IO::Stream ^ fs = openFileDialog1->OpenFile();
				numX=fs->ReadByte();
				numY=fs->ReadByte();
				numericUpDown1->Value=numX;
				numericUpDown2->Value=numY;
				init();
				for(int i=0;i<numX;i++)
				{						
					for(int j=0;j<numY;j++)
					{
						mas[i][j]=fs->ReadByte();
					}
				}
				prep();
				fs->Close();				

				DrawToBuffer( grafx->Graphics );
			    grafx->Render( Graphics::FromHwnd( this->Handle ) );
			 }
		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {

		 }
private: System::Void textBox2_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			 if(sim==1)
				 {
					 if(e->KeyData==Keys::A)	play(0,-1);
					 if(e->KeyData==Keys::D)	play(0,1);
					 if(e->KeyData==Keys::W)	play(-1,0);
					 if(e->KeyData==Keys::S)	play(1,0);
				 }
		 }
private: System::Void button2_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			  if(sim==1)
				 {
					 if(e->KeyData==Keys::A)	play(0,-1);
					 if(e->KeyData==Keys::D)	play(0,1);
					 if(e->KeyData==Keys::W)	play(-1,0);
					 if(e->KeyData==Keys::S)	play(1,0);
				 }
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 prep();
			 DrawToBuffer( grafx->Graphics );
			 grafx->Render( Graphics::FromHwnd( this->Handle ) );
		 }
};
}

