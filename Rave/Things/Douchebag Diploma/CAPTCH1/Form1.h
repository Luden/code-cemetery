#pragma once
#include "stdio.h"
#include "iostream"
#include "fstream"
#include "neubase.h"
#include "noiseform.h"
#include "filters.h"
#include "stat.h"
#include "time.h"
#include "simpleque.h"
#include "analytics.h"

using namespace std;

namespace CAPTCH1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	ofstream log;

	char liters[] = {'a','b','c','d','e','f','g','h','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int numlit = 24;


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
		System::Drawing::Graphics ^ g;
		System::Drawing::Font ^ cfont;
		Bitmap ^ cp;
		Bitmap ^ cp12;
		Bitmap ^ cp2;

		char * code;
		int codelength;
		int cwidth,cheight;
		int ** mas;
		double ** ms1;			// массив для хранения изображения во время интерполяции
		int dim;				// размерность сканирующей матрицы
		int dim2;				// второй слой нейронов
		double *** imgs;
		int ** bboxes;
		int * inds;				// номера пятен		
		int nobr;				// количество образов
		int CurNInd;			// текущий индекс буквы для нормального слова
		bool COMBOBREAKER;		// ручной останов 
		bool PicCreated;
		
		statistic * st;
		filterlist * fl;
		dret * dr;
		network * net;

		int * vshifts;			// сдвиги по вертикали
		int * gshifts;			// сдвиги по горизонтали
		float shperc;			// процент сдвига

	private: System::Windows::Forms::Panel^  panel1;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown5;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown6;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;

	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::FontDialog^  fontDialog1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown7;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::RadioButton^  radioButton3;

	private: System::Windows::Forms::NumericUpDown^  numericUpDown8;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::DataGridView^  dataGridView1;



	private: System::Windows::Forms::NumericUpDown^  numericUpDown10;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown12;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown11;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown13;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown14;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown16;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown17;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown15;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown18;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::DataGridView^  dataGridView2;


private: System::Windows::Forms::CheckBox^  checkBox2;
private: System::Windows::Forms::NumericUpDown^  numericUpDown21;
private: System::Windows::Forms::NumericUpDown^  numericUpDown20;
private: System::Windows::Forms::NumericUpDown^  numericUpDown19;
private: System::Windows::Forms::Label^  label41;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::NumericUpDown^  numericUpDown22;
private: System::Windows::Forms::NumericUpDown^  numericUpDown23;
private: System::Windows::Forms::NumericUpDown^  numericUpDown24;
private: System::Windows::Forms::Label^  label46;
private: System::Windows::Forms::Label^  label44;
private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::Label^  label45;
private: System::Windows::Forms::Label^  label43;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::CheckBox^  checkBox3;










private: System::Windows::Forms::Button^  button13;
private: System::Windows::Forms::Button^  button12;

private: System::Windows::Forms::ListBox^  listBox2;
private: System::Windows::Forms::Button^  button14;
private: System::Windows::Forms::Button^  button16;
private: System::Windows::Forms::Button^  button15;
private: System::Windows::Forms::NumericUpDown^  numericUpDown27;
private: System::Windows::Forms::Label^  label49;
private: System::Windows::Forms::Button^  button18;
private: System::Windows::Forms::Button^  button17;
private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
private: System::Windows::Forms::Button^  button19;

private: System::Windows::Forms::Label^  label50;
private: System::Windows::Forms::Label^  label47;
private: System::Windows::Forms::TextBox^  textBox3;
private: System::Windows::Forms::Label^  label51;
private: System::Windows::Forms::Label^  label52;
private: System::Windows::Forms::CheckBox^  checkBox4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
private: System::Windows::Forms::ProgressBar^  progressBar1;
private: System::Windows::Forms::Button^  button20;
private: System::Windows::Forms::PictureBox^  pictureBox3;
private: System::Windows::Forms::Label^  label54;
private: System::Windows::Forms::Label^  label53;
private: System::Windows::Forms::NumericUpDown^  numericUpDown26;
private: System::Windows::Forms::NumericUpDown^  numericUpDown25;



private: System::Windows::Forms::Label^  label56;
private: System::Windows::Forms::RadioButton^  radioButton4;

private: System::Windows::Forms::NumericUpDown^  numericUpDown28;
private: System::Windows::Forms::RadioButton^  radioButton5;
private: System::Windows::Forms::Label^  label57;
private: System::Windows::Forms::Button^  button21;
private: System::Windows::Forms::Panel^  panel7;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::Label^  label59;
private: System::Windows::Forms::Label^  label58;
private: System::Windows::Forms::NumericUpDown^  numericUpDown29;
private: System::Windows::Forms::Label^  label60;
private: System::Windows::Forms::TextBox^  textBox4;
private: System::Windows::Forms::Label^  label61;
private: System::Windows::Forms::CheckBox^  checkBox5;
private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::GroupBox^  groupBox4;
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::GroupBox^  groupBox7;
private: System::Windows::Forms::GroupBox^  groupBox6;
private: System::Windows::Forms::GroupBox^  groupBox8;
private: System::Windows::Forms::GroupBox^  groupBox9;
private: System::Windows::Forms::GroupBox^  groupBox10;
private: System::Windows::Forms::Label^  label48;
private: System::Windows::Forms::GroupBox^  groupBox13;
private: System::Windows::Forms::GroupBox^  groupBox12;
private: System::Windows::Forms::GroupBox^  groupBox11;
private: System::Windows::Forms::GroupBox^  groupBox16;
private: System::Windows::Forms::GroupBox^  groupBox15;
private: System::Windows::Forms::GroupBox^  groupBox14;





	private: System::Windows::Forms::Label^  label22;
		
	public:		
		Form1(void)
		{
			InitializeComponent();

			log.open("log.txt");
			srand( (unsigned)time( NULL ) );

			cfont = gcnew System::Drawing::Font( FontFamily::GenericSansSerif,36.0F,FontStyle::Regular );
			cwidth = 200;
			cheight = 100;
			
			dim = (int)numericUpDown14->Value;
			dim2 = (int)numericUpDown29->Value;
			double w1 = (double)numericUpDown15->Value; //начальные веса от
			double w2 = (double)numericUpDown16->Value; //до
			double b1 = (double)numericUpDown17->Value; //пороги
			double b2 = (double)numericUpDown18->Value; //до
			double s1 = (double)numericUpDown4->Value;  //скорость обучения

			CurNInd=0;
			COMBOBREAKER = false;
			PicCreated=false;
			fillrows();
			mas = new int * [cwidth];
			ms1 = new double * [cwidth];

			st = new statistic(liters,numlit);
			st->setdiskr((int)numericUpDown1->Value);
			st->setwordlength((int)numericUpDown1->Value);
			st->setcrit(1-(float)numericUpDown7->Value);

			fl = new filterlist();

			for(int i=0;i<cwidth;i++)
			{
				mas[i]=new int [cheight];
				ms1[i]=new double [cheight];
				for(int j=0;j<cheight;j++)
				{
					mas[i][j]=0;
					ms1[i][j]=0;
				}
			}		
			
			fillweightlist();
			reinit(); //инициализация нейросети и таблицы весов нейронов

		}

	
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			log.close();
			if (components)
			{
				delete components;
			}
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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown21 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown22 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown23 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown20 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown24 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown19 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->numericUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown13 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown11 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown10 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown12 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown8 = (gcnew System::Windows::Forms::NumericUpDown());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown27 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown14 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown29 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown15 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown17 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown18 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown16 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown28 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown26 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown25 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->BeginInit();
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown19))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->panel2->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox9->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown13))->BeginInit();
			this->groupBox6->SuspendLayout();
			this->groupBox7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown6))->BeginInit();
			this->groupBox8->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox13->SuspendLayout();
			this->groupBox12->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown29))->BeginInit();
			this->groupBox11->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView2))->BeginInit();
			this->tabPage4->SuspendLayout();
			this->groupBox16->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown3))->BeginInit();
			this->groupBox15->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown28))->BeginInit();
			this->groupBox14->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->panel7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown25))->BeginInit();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->groupBox5);
			this->panel1->Controls->Add(this->groupBox4);
			this->panel1->Controls->Add(this->groupBox3);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Location = System::Drawing::Point(3, 6);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(469, 705);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel1_Paint);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->label4);
			this->groupBox5->Controls->Add(this->numericUpDown2);
			this->groupBox5->Controls->Add(this->label8);
			this->groupBox5->Location = System::Drawing::Point(212, 294);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(244, 82);
			this->groupBox5->TabIndex = 33;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Маскировки";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(66, 31);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(134, 26);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Вероятность появления \r\nмаскирующих элементов";
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(8, 36);
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(48, 20);
			this->numericUpDown2->TabIndex = 5;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(56, 5);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(0, 15);
			this->label8->TabIndex = 6;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->numericUpDown21);
			this->groupBox4->Controls->Add(this->label39);
			this->groupBox4->Controls->Add(this->label38);
			this->groupBox4->Controls->Add(this->checkBox2);
			this->groupBox4->Controls->Add(this->label43);
			this->groupBox4->Controls->Add(this->numericUpDown22);
			this->groupBox4->Controls->Add(this->label45);
			this->groupBox4->Controls->Add(this->label42);
			this->groupBox4->Controls->Add(this->numericUpDown23);
			this->groupBox4->Controls->Add(this->label44);
			this->groupBox4->Controls->Add(this->numericUpDown20);
			this->groupBox4->Controls->Add(this->label46);
			this->groupBox4->Controls->Add(this->numericUpDown24);
			this->groupBox4->Controls->Add(this->label40);
			this->groupBox4->Controls->Add(this->numericUpDown19);
			this->groupBox4->Controls->Add(this->label41);
			this->groupBox4->Location = System::Drawing::Point(213, 385);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(244, 120);
			this->groupBox4->TabIndex = 32;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Нелинейные искажения";
			// 
			// numericUpDown21
			// 
			this->numericUpDown21->DecimalPlaces = 2;
			this->numericUpDown21->Location = System::Drawing::Point(99, 84);
			this->numericUpDown21->Name = L"numericUpDown21";
			this->numericUpDown21->Size = System::Drawing::Size(54, 20);
			this->numericUpDown21->TabIndex = 17;
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(6, 38);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(62, 13);
			this->label39->TabIndex = 6;
			this->label39->Text = L"амплитуда";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(74, 38);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(19, 13);
			this->label38->TabIndex = 6;
			this->label38->Text = L"от";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Location = System::Drawing::Point(9, 16);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(81, 17);
			this->checkBox2->TabIndex = 13;
			this->checkBox2->Text = L"Синусоида";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(74, 63);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(19, 13);
			this->label43->TabIndex = 6;
			this->label43->Text = L"от";
			// 
			// numericUpDown22
			// 
			this->numericUpDown22->DecimalPlaces = 2;
			this->numericUpDown22->Location = System::Drawing::Point(182, 84);
			this->numericUpDown22->Name = L"numericUpDown22";
			this->numericUpDown22->Size = System::Drawing::Size(54, 20);
			this->numericUpDown22->TabIndex = 17;
			this->numericUpDown22->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {6, 0, 0, 0});
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(74, 88);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(19, 13);
			this->label45->TabIndex = 6;
			this->label45->Text = L"от";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(159, 38);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(20, 13);
			this->label42->TabIndex = 6;
			this->label42->Text = L"до";
			// 
			// numericUpDown23
			// 
			this->numericUpDown23->DecimalPlaces = 2;
			this->numericUpDown23->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown23->Location = System::Drawing::Point(182, 59);
			this->numericUpDown23->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			this->numericUpDown23->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown23->Name = L"numericUpDown23";
			this->numericUpDown23->Size = System::Drawing::Size(54, 20);
			this->numericUpDown23->TabIndex = 17;
			this->numericUpDown23->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {16, 0, 0, 65536});
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(159, 63);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(20, 13);
			this->label44->TabIndex = 6;
			this->label44->Text = L"до";
			// 
			// numericUpDown20
			// 
			this->numericUpDown20->DecimalPlaces = 2;
			this->numericUpDown20->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown20->Location = System::Drawing::Point(99, 59);
			this->numericUpDown20->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {2, 0, 0, 0});
			this->numericUpDown20->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown20->Name = L"numericUpDown20";
			this->numericUpDown20->Size = System::Drawing::Size(54, 20);
			this->numericUpDown20->TabIndex = 17;
			this->numericUpDown20->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(159, 88);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(20, 13);
			this->label46->TabIndex = 6;
			this->label46->Text = L"до";
			// 
			// numericUpDown24
			// 
			this->numericUpDown24->DecimalPlaces = 2;
			this->numericUpDown24->Location = System::Drawing::Point(182, 34);
			this->numericUpDown24->Name = L"numericUpDown24";
			this->numericUpDown24->Size = System::Drawing::Size(54, 20);
			this->numericUpDown24->TabIndex = 17;
			this->numericUpDown24->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {16, 0, 0, 0});
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(20, 63);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(48, 13);
			this->label40->TabIndex = 6;
			this->label40->Text = L"частота";
			// 
			// numericUpDown19
			// 
			this->numericUpDown19->DecimalPlaces = 2;
			this->numericUpDown19->Location = System::Drawing::Point(99, 34);
			this->numericUpDown19->Name = L"numericUpDown19";
			this->numericUpDown19->Size = System::Drawing::Size(54, 20);
			this->numericUpDown19->TabIndex = 17;
			this->numericUpDown19->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(2, 88);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(66, 13);
			this->label41->TabIndex = 6;
			this->label41->Text = L"сдвиг фазы";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Controls->Add(this->label12);
			this->groupBox3->Controls->Add(this->numericUpDown1);
			this->groupBox3->Controls->Add(this->radioButton3);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->numericUpDown5);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Controls->Add(this->label22);
			this->groupBox3->Controls->Add(this->label23);
			this->groupBox3->Location = System::Drawing::Point(213, 37);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(243, 248);
			this->groupBox3->TabIndex = 31;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Символьная строка";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(31, 27);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(128, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Выбор шрифта";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(108, 110);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(110, 13);
			this->label12->TabIndex = 6;
			this->label12->Text = L"Сдвиг по вертикали";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(11, 75);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(91, 20);
			this->numericUpDown1->TabIndex = 5;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(31, 228);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(89, 17);
			this->radioButton3->TabIndex = 12;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Ручной ввод";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(107, 80);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(117, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Количество символов";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(31, 205);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(169, 17);
			this->radioButton2->TabIndex = 11;
			this->radioButton2->Text = L"Последовательный перебор";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// numericUpDown5
			// 
			this->numericUpDown5->Location = System::Drawing::Point(11, 105);
			this->numericUpDown5->Name = L"numericUpDown5";
			this->numericUpDown5->Size = System::Drawing::Size(91, 20);
			this->numericUpDown5->TabIndex = 7;
			this->numericUpDown5->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {75, 0, 0, 0});
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(31, 182);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(128, 17);
			this->radioButton1->TabIndex = 10;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Случайные символы";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(11, 137);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(91, 20);
			this->textBox2->TabIndex = 9;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(107, 140);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(94, 13);
			this->label22->TabIndex = 6;
			this->label22->Text = L"Строка символов";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(11, 165);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(131, 13);
			this->label23->TabIndex = 6;
			this->label23->Text = L"Способ создания строки";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(20, 158);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(176, 15);
			this->label7->TabIndex = 6;
			this->label7->Text = L"Добавление строки символов";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(36, 37);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(148, 15);
			this->label6->TabIndex = 6;
			this->label6->Text = L"Добавление маскировок";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(290, 522);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(91, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Создать";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox2->Location = System::Drawing::Point(7, 179);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(200, 100);
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(7, 55);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(200, 100);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(3, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(281, 19);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Создание CAPTCHA изображения";
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(329, 71);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(24, 23);
			this->button16->TabIndex = 34;
			this->button16->Text = L">";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &Form1::button16_Click);
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(299, 71);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(24, 23);
			this->button15->TabIndex = 33;
			this->button15->Text = L"<";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &Form1::button15_Click);
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(366, 71);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(75, 23);
			this->button14->TabIndex = 32;
			this->button14->Text = L"Свойства";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &Form1::button14_Click);
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(366, 42);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(75, 23);
			this->button13->TabIndex = 31;
			this->button13->Text = L"Удалить";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(366, 13);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(75, 23);
			this->button12->TabIndex = 30;
			this->button12->Text = L"Добавить";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &Form1::button12_Click);
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(4, 22);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(289, 69);
			this->listBox2->TabIndex = 28;
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->groupBox10);
			this->panel2->Controls->Add(this->groupBox9);
			this->panel2->Controls->Add(this->groupBox6);
			this->panel2->Controls->Add(this->groupBox7);
			this->panel2->Controls->Add(this->groupBox8);
			this->panel2->Controls->Add(this->pictureBox7);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->pictureBox6);
			this->panel2->Controls->Add(this->label13);
			this->panel2->Controls->Add(this->groupBox2);
			this->panel2->Controls->Add(this->label11);
			this->panel2->Controls->Add(this->label10);
			this->panel2->Controls->Add(this->label9);
			this->panel2->Controls->Add(this->pictureBox5);
			this->panel2->Controls->Add(this->pictureBox4);
			this->panel2->Location = System::Drawing::Point(478, 6);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(463, 705);
			this->panel2->TabIndex = 0;
			this->panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel2_Paint);
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->label19);
			this->groupBox10->Controls->Add(this->label20);
			this->groupBox10->Controls->Add(this->label17);
			this->groupBox10->Controls->Add(this->label18);
			this->groupBox10->Location = System::Drawing::Point(212, 643);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(245, 52);
			this->groupBox10->TabIndex = 25;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Информация";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(12, 16);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(150, 13);
			this->label19->TabIndex = 8;
			this->label19->Text = L"Суммарный процент ошибок";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(168, 16);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(13, 13);
			this->label20->TabIndex = 8;
			this->label20->Text = L"  ";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(11, 30);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(103, 13);
			this->label17->TabIndex = 8;
			this->label17->Text = L"Текущая итерация";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(119, 30);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(16, 13);
			this->label18->TabIndex = 8;
			this->label18->Text = L"   ";
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->button10);
			this->groupBox9->Controls->Add(this->numericUpDown13);
			this->groupBox9->Controls->Add(this->label48);
			this->groupBox9->Controls->Add(this->button5);
			this->groupBox9->Controls->Add(this->checkBox5);
			this->groupBox9->Controls->Add(this->button3);
			this->groupBox9->Location = System::Drawing::Point(212, 535);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(245, 102);
			this->groupBox9->TabIndex = 24;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Тест";
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(117, 15);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(116, 23);
			this->button10->TabIndex = 20;
			this->button10->Text = L"Тестовая выборка";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
			// 
			// numericUpDown13
			// 
			this->numericUpDown13->Location = System::Drawing::Point(17, 30);
			this->numericUpDown13->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			this->numericUpDown13->Name = L"numericUpDown13";
			this->numericUpDown13->Size = System::Drawing::Size(76, 20);
			this->numericUpDown13->TabIndex = 21;
			this->numericUpDown13->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {25, 0, 0, 0});
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(12, 16);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(86, 13);
			this->label48->TabIndex = 6;
			this->label48->Text = L"Обьём выборки";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(117, 73);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(116, 23);
			this->button5->TabIndex = 13;
			this->button5->Text = L"Тест";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(12, 61);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(97, 30);
			this->checkBox5->TabIndex = 23;
			this->checkBox5->Text = L"Использовать\r\nстатистику";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(117, 44);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(116, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Распознание";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->textBox1);
			this->groupBox6->Controls->Add(this->textBox4);
			this->groupBox6->Controls->Add(this->textBox3);
			this->groupBox6->Controls->Add(this->label61);
			this->groupBox6->Controls->Add(this->label14);
			this->groupBox6->Controls->Add(this->label51);
			this->groupBox6->Location = System::Drawing::Point(7, 572);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(199, 123);
			this->groupBox6->TabIndex = 34;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Результаты";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(75, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 9;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(73, 87);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 9;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(73, 49);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 9;
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(9, 90);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(120, 26);
			this->label61->TabIndex = 8;
			this->label61->Text = L"Результат\r\n(с учетом статистики)";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(11, 17);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(95, 26);
			this->label14->TabIndex = 8;
			this->label14->Text = L"Результат\r\n(нейронная сеть)";
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(11, 55);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(126, 26);
			this->label51->TabIndex = 8;
			this->label51->Text = L"Результат \r\n(аналитический метод)";
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->button8);
			this->groupBox7->Controls->Add(this->numericUpDown4);
			this->groupBox7->Controls->Add(this->label15);
			this->groupBox7->Controls->Add(this->label16);
			this->groupBox7->Controls->Add(this->numericUpDown6);
			this->groupBox7->Controls->Add(this->button9);
			this->groupBox7->Controls->Add(this->button6);
			this->groupBox7->Controls->Add(this->button4);
			this->groupBox7->Location = System::Drawing::Point(212, 138);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(245, 147);
			this->groupBox7->TabIndex = 23;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Обучение";
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(89, 70);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(27, 23);
			this->button8->TabIndex = 19;
			this->button8->Text = L"<";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click_1);
			// 
			// numericUpDown4
			// 
			this->numericUpDown4->DecimalPlaces = 10;
			this->numericUpDown4->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 393216});
			this->numericUpDown4->Location = System::Drawing::Point(161, 70);
			this->numericUpDown4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->numericUpDown4->Name = L"numericUpDown4";
			this->numericUpDown4->Size = System::Drawing::Size(78, 20);
			this->numericUpDown4->TabIndex = 12;
			this->numericUpDown4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {25, 0, 0, 196608});
			this->numericUpDown4->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown4_ValueChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(18, 54);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(78, 39);
			this->label15->TabIndex = 6;
			this->label15->Text = L"Коеффициент\r\nскорости \r\nобучения";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(18, 22);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(121, 26);
			this->label16->TabIndex = 6;
			this->label16->Text = L"Количество итераций \r\nобучения";
			// 
			// numericUpDown6
			// 
			this->numericUpDown6->Location = System::Drawing::Point(161, 28);
			this->numericUpDown6->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
			this->numericUpDown6->Name = L"numericUpDown6";
			this->numericUpDown6->Size = System::Drawing::Size(78, 20);
			this->numericUpDown6->TabIndex = 15;
			this->numericUpDown6->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {500, 0, 0, 0});
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(122, 70);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(27, 23);
			this->button9->TabIndex = 19;
			this->button9->Text = L">";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(12, 110);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(108, 23);
			this->button6->TabIndex = 14;
			this->button6->Text = L"Обучить";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(125, 110);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(108, 23);
			this->button4->TabIndex = 16;
			this->button4->Text = L"Обучение полное";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->numericUpDown11);
			this->groupBox8->Controls->Add(this->numericUpDown10);
			this->groupBox8->Controls->Add(this->numericUpDown7);
			this->groupBox8->Controls->Add(this->button7);
			this->groupBox8->Controls->Add(this->label21);
			this->groupBox8->Controls->Add(this->label26);
			this->groupBox8->Controls->Add(this->numericUpDown12);
			this->groupBox8->Controls->Add(this->label24);
			this->groupBox8->Controls->Add(this->label27);
			this->groupBox8->Controls->Add(this->label28);
			this->groupBox8->Controls->Add(this->numericUpDown8);
			this->groupBox8->Location = System::Drawing::Point(212, 294);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(245, 235);
			this->groupBox8->TabIndex = 23;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Критерии остановки обучения";
			// 
			// numericUpDown11
			// 
			this->numericUpDown11->Location = System::Drawing::Point(159, 140);
			this->numericUpDown11->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown11->Name = L"numericUpDown11";
			this->numericUpDown11->Size = System::Drawing::Size(78, 20);
			this->numericUpDown11->TabIndex = 17;
			this->numericUpDown11->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// numericUpDown10
			// 
			this->numericUpDown10->Location = System::Drawing::Point(161, 78);
			this->numericUpDown10->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->numericUpDown10->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown10->Name = L"numericUpDown10";
			this->numericUpDown10->Size = System::Drawing::Size(78, 20);
			this->numericUpDown10->TabIndex = 17;
			this->numericUpDown10->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			// 
			// numericUpDown7
			// 
			this->numericUpDown7->DecimalPlaces = 2;
			this->numericUpDown7->Location = System::Drawing::Point(161, 28);
			this->numericUpDown7->Name = L"numericUpDown7";
			this->numericUpDown7->Size = System::Drawing::Size(78, 20);
			this->numericUpDown7->TabIndex = 17;
			this->numericUpDown7->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown7_ValueChanged);
			// 
			// button7
			// 
			this->button7->Enabled = false;
			this->button7->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->button7->ForeColor = System::Drawing::Color::Red;
			this->button7->Location = System::Drawing::Point(80, 198);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(83, 30);
			this->button7->TabIndex = 18;
			this->button7->Text = L"останов";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(19, 22);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(90, 26);
			this->label21->TabIndex = 6;
			this->label21->Text = L"Допустимый\r\nпроцент ошибок";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(19, 59);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(128, 39);
			this->label26->TabIndex = 6;
			this->label26->Text = L"Проверка возможности \r\nостановки обучения \r\nчерез каждые";
			// 
			// numericUpDown12
			// 
			this->numericUpDown12->Location = System::Drawing::Point(159, 166);
			this->numericUpDown12->Name = L"numericUpDown12";
			this->numericUpDown12->Size = System::Drawing::Size(78, 20);
			this->numericUpDown12->TabIndex = 17;
			this->numericUpDown12->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(19, 107);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(121, 26);
			this->label24->TabIndex = 6;
			this->label24->Text = L"Пересчёт процента \r\nошибок через каждые";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(19, 142);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(137, 13);
			this->label27->TabIndex = 6;
			this->label27->Text = L"Объём тестовой выборки";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(19, 162);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(122, 26);
			this->label28->TabIndex = 6;
			this->label28->Text = L"Минимальный процент\r\nуспешно обученных";
			// 
			// numericUpDown8
			// 
			this->numericUpDown8->Location = System::Drawing::Point(160, 107);
			this->numericUpDown8->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown8->Name = L"numericUpDown8";
			this->numericUpDown8->Size = System::Drawing::Size(78, 20);
			this->numericUpDown8->TabIndex = 17;
			this->numericUpDown8->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->numericUpDown8->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown8_ValueChanged);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox7->Location = System::Drawing::Point(6, 522);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(200, 44);
			this->pictureBox7->TabIndex = 1;
			this->pictureBox7->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(3, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(308, 19);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Распознание CAPTCHA изображения";
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox6->Location = System::Drawing::Point(6, 398);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(200, 100);
			this->pictureBox6->TabIndex = 1;
			this->pictureBox6->TabStop = false;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(57, 501);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(94, 15);
			this->label13->TabIndex = 6;
			this->label13->Text = L"Нормализация";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->button15);
			this->groupBox2->Controls->Add(this->numericUpDown27);
			this->groupBox2->Controls->Add(this->button16);
			this->groupBox2->Controls->Add(this->listBox2);
			this->groupBox2->Controls->Add(this->label49);
			this->groupBox2->Controls->Add(this->button14);
			this->groupBox2->Controls->Add(this->button12);
			this->groupBox2->Controls->Add(this->button13);
			this->groupBox2->Location = System::Drawing::Point(6, 32);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(447, 100);
			this->groupBox2->TabIndex = 30;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Шумоподавление";
			// 
			// numericUpDown27
			// 
			this->numericUpDown27->DecimalPlaces = 2;
			this->numericUpDown27->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
			this->numericUpDown27->Location = System::Drawing::Point(307, 45);
			this->numericUpDown27->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown27->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 131072});
			this->numericUpDown27->Name = L"numericUpDown27";
			this->numericUpDown27->Size = System::Drawing::Size(46, 20);
			this->numericUpDown27->TabIndex = 22;
			this->numericUpDown27->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 65536});
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Location = System::Drawing::Point(305, 18);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(48, 26);
			this->label49->TabIndex = 6;
			this->label49->Text = L"Порог\r\nяркости";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(39, 380);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(131, 15);
			this->label11->TabIndex = 6;
			this->label11->Text = L"Выделение символов";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(37, 259);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(135, 15);
			this->label10->TabIndex = 6;
			this->label10->Text = L"Удаление маскировок";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(33, 135);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(143, 15);
			this->label9->TabIndex = 6;
			this->label9->Text = L"Исходное изображение";
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox5->Location = System::Drawing::Point(6, 277);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(200, 100);
			this->pictureBox5->TabIndex = 1;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->pictureBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox4->Location = System::Drawing::Point(6, 153);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(200, 100);
			this->pictureBox4->TabIndex = 1;
			this->pictureBox4->TabStop = false;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label25->Location = System::Drawing::Point(5, 5);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(162, 15);
			this->label25->TabIndex = 6;
			this->label25->Text = L"Статистика распознавания";
			// 
			// fontDialog1
			// 
			this->fontDialog1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			this->fontDialog1->MaxSize = 43;
			this->fontDialog1->MinSize = 16;
			this->fontDialog1->ScriptsOnly = true;
			this->fontDialog1->ShowEffects = false;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->Column1, 
				this->Column2, this->Column3, this->Column4});
			this->dataGridView1->Location = System::Drawing::Point(8, 48);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(330, 567);
			this->dataGridView1->TabIndex = 19;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellContentClick);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Символ";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 50;
			// 
			// Column2
			// 
			this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Column2->HeaderText = L"% текущий";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Width = 84;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"% всего";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->Width = 83;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"% с аналитикой";
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(957, 744);
			this->tabControl1->TabIndex = 13;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(949, 718);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Главная";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->groupBox13);
			this->tabPage2->Controls->Add(this->groupBox12);
			this->tabPage2->Controls->Add(this->groupBox11);
			this->tabPage2->Controls->Add(this->dataGridView2);
			this->tabPage2->Controls->Add(this->listBox1);
			this->tabPage2->Controls->Add(this->label37);
			this->tabPage2->Controls->Add(this->button11);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(949, 718);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Нейросеть";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// groupBox13
			// 
			this->groupBox13->Controls->Add(this->button17);
			this->groupBox13->Controls->Add(this->button18);
			this->groupBox13->Location = System::Drawing::Point(16, 297);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Size = System::Drawing::Size(224, 51);
			this->groupBox13->TabIndex = 15;
			this->groupBox13->TabStop = false;
			this->groupBox13->Text = L"Файл";
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(34, 16);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(75, 23);
			this->button17->TabIndex = 10;
			this->button17->Text = L"сохранить";
			this->button17->UseVisualStyleBackColor = true;
			this->button17->Click += gcnew System::EventHandler(this, &Form1::button17_Click);
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(115, 16);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(75, 23);
			this->button18->TabIndex = 11;
			this->button18->Text = L"загрузить";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &Form1::button18_Click);
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->label29);
			this->groupBox12->Controls->Add(this->numericUpDown14);
			this->groupBox12->Controls->Add(this->numericUpDown29);
			this->groupBox12->Controls->Add(this->label30);
			this->groupBox12->Controls->Add(this->checkBox3);
			this->groupBox12->Controls->Add(this->label60);
			this->groupBox12->Location = System::Drawing::Point(14, 142);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(236, 149);
			this->groupBox12->TabIndex = 14;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Сеть";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(69, 21);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(27, 13);
			this->label29->TabIndex = 1;
			this->label29->Text = L"n  =";
			// 
			// numericUpDown14
			// 
			this->numericUpDown14->Location = System::Drawing::Point(102, 19);
			this->numericUpDown14->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {32, 0, 0, 0});
			this->numericUpDown14->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->numericUpDown14->Name = L"numericUpDown14";
			this->numericUpDown14->Size = System::Drawing::Size(38, 20);
			this->numericUpDown14->TabIndex = 0;
			this->numericUpDown14->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {16, 0, 0, 0});
			// 
			// numericUpDown29
			// 
			this->numericUpDown29->Location = System::Drawing::Point(198, 111);
			this->numericUpDown29->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {256, 0, 0, 0});
			this->numericUpDown29->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->numericUpDown29->Name = L"numericUpDown29";
			this->numericUpDown29->Size = System::Drawing::Size(38, 20);
			this->numericUpDown29->TabIndex = 12;
			this->numericUpDown29->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {32, 0, 0, 0});
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(13, 42);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(204, 39);
			this->label30->TabIndex = 2;
			this->label30->Text = L"сканирующая матрица nxn элементов\r\nвходной слой нейронов nxn элементов\r\n\r\n";
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(11, 88);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->checkBox3->Size = System::Drawing::Size(201, 17);
			this->checkBox3->TabIndex = 9;
			this->checkBox3->Text = L"Добавить скрытый слой нейронов";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(6, 113);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(195, 13);
			this->label60->TabIndex = 1;
			this->label60->Text = L"Количество нейронов скрытого слоя";
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->label31);
			this->groupBox11->Controls->Add(this->numericUpDown15);
			this->groupBox11->Controls->Add(this->numericUpDown17);
			this->groupBox11->Controls->Add(this->numericUpDown18);
			this->groupBox11->Controls->Add(this->numericUpDown16);
			this->groupBox11->Controls->Add(this->label32);
			this->groupBox11->Controls->Add(this->label35);
			this->groupBox11->Controls->Add(this->label36);
			this->groupBox11->Controls->Add(this->label34);
			this->groupBox11->Controls->Add(this->label33);
			this->groupBox11->Location = System::Drawing::Point(13, 27);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(237, 109);
			this->groupBox11->TabIndex = 13;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Нейрон";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(14, 16);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(139, 13);
			this->label31->TabIndex = 5;
			this->label31->Text = L"Начальные веса синапсов";
			// 
			// numericUpDown15
			// 
			this->numericUpDown15->DecimalPlaces = 2;
			this->numericUpDown15->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown15->Location = System::Drawing::Point(39, 32);
			this->numericUpDown15->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, -2147483648});
			this->numericUpDown15->Name = L"numericUpDown15";
			this->numericUpDown15->Size = System::Drawing::Size(60, 20);
			this->numericUpDown15->TabIndex = 4;
			this->numericUpDown15->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			// 
			// numericUpDown17
			// 
			this->numericUpDown17->DecimalPlaces = 2;
			this->numericUpDown17->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown17->Location = System::Drawing::Point(39, 78);
			this->numericUpDown17->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, -2147483648});
			this->numericUpDown17->Name = L"numericUpDown17";
			this->numericUpDown17->Size = System::Drawing::Size(60, 20);
			this->numericUpDown17->TabIndex = 4;
			// 
			// numericUpDown18
			// 
			this->numericUpDown18->DecimalPlaces = 2;
			this->numericUpDown18->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown18->Location = System::Drawing::Point(126, 78);
			this->numericUpDown18->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, -2147483648});
			this->numericUpDown18->Name = L"numericUpDown18";
			this->numericUpDown18->Size = System::Drawing::Size(60, 20);
			this->numericUpDown18->TabIndex = 4;
			// 
			// numericUpDown16
			// 
			this->numericUpDown16->DecimalPlaces = 2;
			this->numericUpDown16->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown16->Location = System::Drawing::Point(126, 32);
			this->numericUpDown16->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, -2147483648});
			this->numericUpDown16->Name = L"numericUpDown16";
			this->numericUpDown16->Size = System::Drawing::Size(60, 20);
			this->numericUpDown16->TabIndex = 4;
			this->numericUpDown16->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(14, 34);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(19, 13);
			this->label32->TabIndex = 6;
			this->label32->Text = L"от";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(14, 80);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(19, 13);
			this->label35->TabIndex = 6;
			this->label35->Text = L"от";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(100, 80);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(20, 13);
			this->label36->TabIndex = 6;
			this->label36->Text = L"до";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(14, 62);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(37, 13);
			this->label34->TabIndex = 6;
			this->label34->Text = L"Порог";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(100, 34);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(20, 13);
			this->label33->TabIndex = 6;
			this->label33->Text = L"до";
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Tahoma", 8));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle1->NullValue = nullptr;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView2->DefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView2->Location = System::Drawing::Point(308, 48);
			this->dataGridView2->MultiSelect = false;
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->ReadOnly = true;
			this->dataGridView2->RowHeadersWidth = 50;
			this->dataGridView2->RowTemplate->DefaultCellStyle->Format = L"N2";
			this->dataGridView2->RowTemplate->DefaultCellStyle->NullValue = nullptr;
			this->dataGridView2->Size = System::Drawing::Size(621, 510);
			this->dataGridView2->TabIndex = 8;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(256, 48);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(46, 511);
			this->listBox1->TabIndex = 7;
			this->listBox1->Click += gcnew System::EventHandler(this, &Form1::listBox1_Click);
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(273, 27);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(270, 13);
			this->label37->TabIndex = 6;
			this->label37->Text = L"Веса входящих синапсов выходного слоя нейронов";
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(91, 366);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(75, 23);
			this->button11->TabIndex = 3;
			this->button11->Text = L"Создать";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &Form1::button11_Click);
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->groupBox16);
			this->tabPage4->Controls->Add(this->groupBox15);
			this->tabPage4->Controls->Add(this->groupBox14);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(949, 718);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Аналитика";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// groupBox16
			// 
			this->groupBox16->Controls->Add(this->label56);
			this->groupBox16->Controls->Add(this->radioButton5);
			this->groupBox16->Controls->Add(this->checkBox4);
			this->groupBox16->Controls->Add(this->radioButton4);
			this->groupBox16->Controls->Add(this->label47);
			this->groupBox16->Controls->Add(this->button19);
			this->groupBox16->Controls->Add(this->label50);
			this->groupBox16->Controls->Add(this->numericUpDown3);
			this->groupBox16->Location = System::Drawing::Point(27, 18);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(198, 252);
			this->groupBox16->TabIndex = 10;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"Аналитика";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(27, 27);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(116, 13);
			this->label56->TabIndex = 3;
			this->label56->Text = L"Обучающая выборка";
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(30, 188);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(133, 30);
			this->radioButton5->TabIndex = 3;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"Использовать метод \r\nближайших соседей";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Enabled = false;
			this->checkBox4->Location = System::Drawing::Point(30, 116);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(137, 30);
			this->checkBox4->TabIndex = 5;
			this->checkBox4->Text = L"Использовать \r\nаналитический метод";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Checked = true;
			this->radioButton4->Location = System::Drawing::Point(30, 152);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(138, 30);
			this->radioButton4->TabIndex = 7;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Использовать метод\r\nдробящихся эталонов";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(111, 88);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(13, 13);
			this->label47->TabIndex = 2;
			this->label47->Text = L"0";
			// 
			// button19
			// 
			this->button19->Location = System::Drawing::Point(95, 43);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(75, 23);
			this->button19->TabIndex = 0;
			this->button19->Text = L"выбрать";
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Click += gcnew System::EventHandler(this, &Form1::button19_Click);
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(49, 88);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(56, 13);
			this->label50->TabIndex = 3;
			this->label50->Text = L"Итерация";
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Location = System::Drawing::Point(30, 46);
			this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {5000, 0, 0, 0});
			this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(59, 20);
			this->numericUpDown3->TabIndex = 1;
			this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			// 
			// groupBox15
			// 
			this->groupBox15->Controls->Add(this->numericUpDown28);
			this->groupBox15->Controls->Add(this->label57);
			this->groupBox15->Location = System::Drawing::Point(508, 23);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Size = System::Drawing::Size(228, 96);
			this->groupBox15->TabIndex = 9;
			this->groupBox15->TabStop = false;
			this->groupBox15->Text = L"Метод ближайших соседей";
			// 
			// numericUpDown28
			// 
			this->numericUpDown28->DecimalPlaces = 5;
			this->numericUpDown28->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 196608});
			this->numericUpDown28->Location = System::Drawing::Point(68, 38);
			this->numericUpDown28->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 327680});
			this->numericUpDown28->Name = L"numericUpDown28";
			this->numericUpDown28->Size = System::Drawing::Size(70, 20);
			this->numericUpDown28->TabIndex = 4;
			this->numericUpDown28->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {15, 0, 0, 131072});
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(19, 41);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(43, 13);
			this->label57->TabIndex = 2;
			this->label57->Text = L"Радиус";
			// 
			// groupBox14
			// 
			this->groupBox14->Controls->Add(this->button21);
			this->groupBox14->Controls->Add(this->label52);
			this->groupBox14->Controls->Add(this->progressBar1);
			this->groupBox14->Location = System::Drawing::Point(248, 20);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Size = System::Drawing::Size(237, 99);
			this->groupBox14->TabIndex = 8;
			this->groupBox14->TabStop = false;
			this->groupBox14->Text = L"Метод дробящихся эталонов";
			// 
			// button21
			// 
			this->button21->Location = System::Drawing::Point(59, 30);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(112, 23);
			this->button21->TabIndex = 8;
			this->button21->Text = L"Инициализировать";
			this->button21->UseVisualStyleBackColor = true;
			this->button21->Click += gcnew System::EventHandler(this, &Form1::button21_Click);
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(80, 67);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(72, 13);
			this->label52->TabIndex = 4;
			this->label52->Text = L"Ожидайте...";
			this->label52->Visible = false;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(32, 83);
			this->progressBar1->Maximum = 24;
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(166, 10);
			this->progressBar1->Step = 1;
			this->progressBar1->TabIndex = 6;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->groupBox1);
			this->tabPage3->Controls->Add(this->panel7);
			this->tabPage3->Controls->Add(this->label54);
			this->tabPage3->Controls->Add(this->label53);
			this->tabPage3->Controls->Add(this->numericUpDown26);
			this->tabPage3->Controls->Add(this->numericUpDown25);
			this->tabPage3->Controls->Add(this->button20);
			this->tabPage3->Controls->Add(this->checkBox1);
			this->tabPage3->Controls->Add(this->dataGridView1);
			this->tabPage3->Controls->Add(this->label25);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(949, 718);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Статистика";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label59);
			this->groupBox1->Controls->Add(this->label58);
			this->groupBox1->Location = System::Drawing::Point(353, 388);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(316, 86);
			this->groupBox1->TabIndex = 27;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Легенда";
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->ForeColor = System::Drawing::Color::Green;
			this->label59->Location = System::Drawing::Point(15, 50);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(284, 13);
			this->label59->TabIndex = 0;
			this->label59->Text = L"Процент верно распознанных аналитическим методом";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->ForeColor = System::Drawing::Color::Red;
			this->label58->Location = System::Drawing::Point(15, 26);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(250, 13);
			this->label58->TabIndex = 0;
			this->label58->Text = L"Процент верно распознанных нейронной сетью";
			// 
			// panel7
			// 
			this->panel7->AutoScroll = true;
			this->panel7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel7->Controls->Add(this->pictureBox3);
			this->panel7->Location = System::Drawing::Point(353, 48);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(576, 334);
			this->panel7->TabIndex = 26;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(2, 2);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(565, 320);
			this->pictureBox3->TabIndex = 23;
			this->pictureBox3->TabStop = false;
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(651, 19);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(79, 13);
			this->label54->TabIndex = 25;
			this->label54->Text = L"Масштаб по  y";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(506, 19);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(79, 13);
			this->label53->TabIndex = 25;
			this->label53->Text = L"Масштаб по  x";
			// 
			// numericUpDown26
			// 
			this->numericUpDown26->DecimalPlaces = 2;
			this->numericUpDown26->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown26->Location = System::Drawing::Point(736, 17);
			this->numericUpDown26->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown26->Name = L"numericUpDown26";
			this->numericUpDown26->Size = System::Drawing::Size(54, 20);
			this->numericUpDown26->TabIndex = 24;
			this->numericUpDown26->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {22, 0, 0, 65536});
			// 
			// numericUpDown25
			// 
			this->numericUpDown25->DecimalPlaces = 2;
			this->numericUpDown25->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->numericUpDown25->Location = System::Drawing::Point(591, 17);
			this->numericUpDown25->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown25->Name = L"numericUpDown25";
			this->numericUpDown25->Size = System::Drawing::Size(54, 20);
			this->numericUpDown25->TabIndex = 24;
			this->numericUpDown25->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {22, 0, 0, 65536});
			// 
			// button20
			// 
			this->button20->Location = System::Drawing::Point(353, 13);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(115, 24);
			this->button20->TabIndex = 22;
			this->button20->Text = L"Построить график";
			this->button20->UseVisualStyleBackColor = true;
			this->button20->Click += gcnew System::EventHandler(this, &Form1::button20_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(8, 25);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(138, 17);
			this->checkBox1->TabIndex = 20;
			this->checkBox1->Text = L"выводить статистику";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->ClientSize = System::Drawing::Size(957, 744);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CAPTCH1";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown19))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown13))->EndInit();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown6))->EndInit();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->groupBox13->ResumeLayout(false);
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown29))->EndInit();
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView2))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->groupBox16->ResumeLayout(false);
			this->groupBox16->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown3))->EndInit();
			this->groupBox15->ResumeLayout(false);
			this->groupBox15->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown28))->EndInit();
			this->groupBox14->ResumeLayout(false);
			this->groupBox14->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->panel7->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown25))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

char * GenText()
{
	//------------------------------------------------------------------
	//		Общая форма создания текста
	//------------------------------------------------------------------

	if(radioButton1->Checked==true) return GetRandomWord();
	if(radioButton2->Checked==true) return GetNormalWord();
	if(radioButton3->Checked==true) return GetManualWord();	
}

void MakeVertShifts(float textheight)
{
	//------------------------------------------------------------------
	//		Создание вертикальных сдвигов
	//------------------------------------------------------------------

	Random ^ rd = gcnew Random();
	vshifts = new int[codelength];
	for(int i=0;i<codelength;i++)
	{
		vshifts[i] = (cheight-textheight)*(rd->NextDouble()-0.5)*shperc;
	}
}

void MakeGorShifts(Graphics ^ g)
{
	//------------------------------------------------------------------
	//		Создание горизонтальных сдвигов
	//------------------------------------------------------------------
	
	System::Drawing::SizeF tesize;
	Random ^ rd = gcnew Random();
	gshifts = new int[codelength];
	
	for(int i=0;i<codelength;i++)gshifts[i]=0;

	for(int i=0;i<codelength;i++)
	{
		String ^ scode = gcnew  String(&code[i],0,1);
		tesize = g->MeasureString( scode, cfont);
		if(i!=codelength-1)gshifts[i+1] += (tesize.Width + gshifts[i] - cfont->SizeInPoints/2 + 5); //учесть растояние между буквами (+2) и функции measureString (-17)
		//log<<gshifts[i]<<" * "<<tesize.Width<<" - ";
	}
	//log<<endl;
}

void AddText(Graphics ^ g, Brush ^ cbrush, int xpos, int ypos)
{
	//------------------------------------------------------------------
	//		Добавление текста
	//------------------------------------------------------------------

	System::Drawing::Graphics ^ g2 = g;

	if(checkBox2->Checked)
	{//если надо внести нелинейные искажения, то мы создаём новый слой с белым цветом			
		cp2 = gcnew Bitmap(cwidth,cheight);
		g = System::Drawing::Graphics::FromImage(cp2);
		g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);
	}

	for(int i=0;i<codelength;i++)
	{//вносим на него строку символов
		String ^ scode = gcnew  String(&code[i],0,1);
		g->DrawString(scode,cfont,cbrush,xpos+gshifts[i],ypos+vshifts[i]);
	}
	
	if(checkBox2->Checked)
	{//искажаем строку и переносим её на наш фон

		double amp1 = (double)numericUpDown19->Value;
		double freq1 = (double)numericUpDown20->Value;
		double phi1 = (double)numericUpDown21->Value;

		double amp2 = (double)numericUpDown24->Value;
		double freq2 = (double)numericUpDown23->Value;
		double phi2 = (double)numericUpDown22->Value;

		double amp;
		double freq;
		double phi;

		if(amp2-amp1<=0)amp=amp1;
		else amp = rand()%(int)(amp2-amp1)+amp1;
		if(freq2-freq1<=0)freq=freq1;
		else freq = ((double)(rand()%(int)((freq2-freq1)*100)))/(double)100+freq1;
		log<<"freq="<<freq<<endl;
		if(phi2-phi1<=0)phi=phi1;
		else phi = rand()%(int)(phi2-phi1)+phi1;

		double coef;
		double tcoef = 2*Math::PI/cwidth;
		
		int pix;

		for(int i=0;i<cwidth;i++)
		{
			double coef=Math::Sin(i*tcoef*freq+phi);

			for(int j=0;j<cheight;j++)
			{
				Color pixc = cp2->GetPixel(i,j);
				
				if(pixc.R>110)continue; //белые невсчёт!

				pix = j+amp*coef;
				if((pix>=0)&&(pix<cheight)) //если пиксел не улетел за экран
				{
					cp->SetPixel(i,pix,pixc);
				}
			}
		}

		g=g2; //возвращаем назад наш графикс
	}
}


void adnoise(Graphics ^ g)
{
	//------------------------------------------------------------------
	//		Добавление шума
	//------------------------------------------------------------------

	Random ^ rd = gcnew Random();
	int ver = (int) numericUpDown2->Value;
	Color clr = System::Drawing::Color::FromArgb(255,0,0,0);
	Pen ^ mypen = gcnew System::Drawing::Pen(clr);

	for(int i=0;i<cwidth;i++)
	{
		for(int j=0;j<cheight;j++)
		{
			if(rd->NextDouble()*100<ver)
			{					
				cp->SetPixel(i,j,clr);
			}
		}
	}
}


void remnoise()
{	
	//------------------------------------------------------------------
	//		Удаление шума
	//------------------------------------------------------------------

	double ** mas = new double * [cwidth];
	for(int i=0;i<cwidth;i++)
	{
		mas[i] = new double [cheight];
		for(int j=0;j<cheight;j++)
		{
			Color col1 = cp->GetPixel(i,j);
			mas[i][j]=1-((double)col1.G)/255;
		}
	}

	fl->doit(mas);

	for(int i=0;i<cwidth;i++)
	{		
		for(int j=0;j<cheight;j++)
		{
			int bri = (1-mas[i][j])*255;
			Color col1 = Color::FromArgb(255,bri,bri,bri);			
			cp->SetPixel(i,j,col1);
		}
	}

}


void marker(int x1,int y1)
{	
	//------------------------------------------------------------------
	//		Выделение пятна
	//------------------------------------------------------------------

	simpleq * qq = new simpleq();

	int x = x1;
	int y = y1;

	qq->add(x,y);

	while(qq->get(x,y))
	{
		Color cl1 = cp->GetPixel(x,y);
		double bri = 1-((double)cl1.R/255);
		double bri1 = (double)numericUpDown27->Value;
		if((bri>=bri1)&&(mas[x][y]==0))
		{			
			mas[x][y]=nobr;
			if(x>0)qq->add(x-1,y);
			if(x<cwidth-1)qq->add(x+1,y);
			if(y>0)qq->add(x,y-1);
			if(y<cheight-1)qq->add(x,y+1);

			if((x>0)&&(y>0))qq->add(x-1,y-1);
			if((x<cwidth-1)&&(y<cheight-1))qq->add(x+1,y+1);
			if((y>0)&&(x<cwidth-1))qq->add(x+1,y-1);
			if((y<cheight-1)&&(x>0))qq->add(x-1,y+1);
		}
	}
}

void sort(double * ss)
{
	//------------------------------------------------------------------
	//		Сортировка по убыванию
	//------------------------------------------------------------------

	for(int i=0;i<nobr;i++)
	{
		double max=ss[i];
		int ind=i;
		for(int j=i;j<nobr;j++)
		{
			if(ss[j]>max)
			{
				max = ss[j];
				ind = j;
			}
		}
		double temp = ss[i];
		ss[i] = ss[ind];
		ss[ind]=temp;

		int temp2 = inds[i];
		inds[i] = inds[ind];
		inds[ind] = temp2;
	}
}

void recorrect()
{
	//------------------------------------------------------------------
	//		Корректировка рамок по порядку
	//------------------------------------------------------------------

	double * ss = new double[nobr];	
	for(int i=0;i<nobr;i++)
	{		
		ss[i] = cwidth-bboxes[i][0];		
		log<<inds[i]<<" ";
	}
	log<<endl;
	sort(ss);	

	int ** temp = new int * [nobr];
	for(int i=0;i<nobr;i++)
	{
		temp[i] = new int[4];		
		for(int k=0;k<nobr;k++)
		{
			if(ss[i]==cwidth-bboxes[k][0])
			{
				for(int j=0;j<4;j++)
				{					
					temp[i][j] = bboxes[k][j];
				}
			}
		}			
		
	}

	for(int i=0;i<codelength;i++)
	{		
		for(int j=0;j<4;j++)
		{
			bboxes[i][j] = temp[i][j];
		}
	}
}

void correctboxes()
{
	//------------------------------------------------------------------
	//		Корректировка рамок по количеству
	//------------------------------------------------------------------

	if(nobr==codelength)
	{		
		inds = new int[nobr];
		for(int i=0;i<nobr;i++)
		{
			inds[i]=i;
		}
		return;
	}

	if(nobr>codelength)
	{
		double * ss = new double[nobr];
		inds = new int[nobr];
		for(int i=0;i<nobr;i++)
		{
			double w = bboxes[i][1]-bboxes[i][0];
			double h = bboxes[i][3]-bboxes[i][2];
			ss[i] = w*h;
			inds[i]=i;
		}
		sort(ss);	

		int ** temp = new int * [codelength];
		for(int i=0;i<codelength;i++)
		{
			temp[i] = new int[4];
			for(int j=0;j<4;j++)
			{
				temp[i][j] = bboxes[inds[i]][j];
			}
		}

		for(int i=0;i<nobr;i++)
		{
			delete(bboxes[i]);
		}
		delete(bboxes);

		bboxes = new int * [codelength];
		for(int i=0;i<codelength;i++)
		{
			bboxes[i] = new int[4];
			for(int j=0;j<4;j++)
			{
				bboxes[i][j] = temp[i][j];
			}
		}

		nobr = codelength;
		
		recorrect();

		return;
	}

	if(nobr<codelength)
	{
		inds = new int[codelength];
		for(int i=0;i<codelength;i++)
		{			
			inds[i]=i;
		}

		while(nobr<codelength)
		{
			double * ss = new double[nobr];			
			for(int i=0;i<nobr;i++)
			{
				double w = bboxes[i][1]-bboxes[i][0];
				double h = bboxes[i][3]-bboxes[i][2];
				ss[i] = w*h;				
			}
			sort(ss);			

			int ** temp = new int * [nobr+1];
			for(int i=1;i<nobr;i++)
			{
				temp[i] = new int[4];
				for(int j=0;j<4;j++)
				{
					temp[i][j] = bboxes[inds[i]][j];
				}
			}
			
			int mid = (bboxes[inds[0]][1]-bboxes[inds[0]][0])/2;
				
			temp[0] = new int[4];
			temp[nobr] = new int[4];

			temp[0][0] = bboxes[inds[0]][0]; 
			temp[0][1] = mid+bboxes[inds[0]][0];
			temp[0][2] = bboxes[inds[0]][2]; 
			temp[0][3] = bboxes[inds[0]][3];

			temp[nobr][0] = mid+bboxes[inds[0]][0]; 
			temp[nobr][1] = bboxes[inds[0]][1];
			temp[nobr][2] = bboxes[inds[0]][2]; 
			temp[nobr][3] = bboxes[inds[0]][3];

			for(int i=temp[nobr][0];i<=temp[nobr][1];i++)
			{
				for(int j=temp[nobr][2];j<=temp[nobr][3];j++)
				{
					if(mas[i][j]==(inds[0]+1))
					{
						mas[i][j]=nobr+1;
					}
				}
			}

			for(int i=0;i<nobr;i++)
			{
				delete(bboxes[i]);
			}
			delete(bboxes);

			bboxes = new int * [nobr+1];
			for(int i=0;i<nobr+1;i++)
			{
				bboxes[i] = new int[4];
				for(int j=0;j<4;j++)
				{
					bboxes[i][j] = temp[i][j];
				}
			}

			nobr++;
		}

		recorrect();
	}
}


bool checkarea()
{
	//------------------------------------------------------------------
	//		Корректировка рамок по размеру
	//------------------------------------------------------------------

	for(int i=0;i<nobr;i++)
	{
		if((bboxes[i][1] - bboxes[i][0])<4){nobr=0;return 0;}
		if((bboxes[i][3] - bboxes[i][2])<4){nobr=0;return 0;}
	}
	return 1;
}

void findletters()
{
	//------------------------------------------------------------------
	//		Поиск символов на изображении
	//------------------------------------------------------------------

	double bri1 = (double)numericUpDown27->Value;

	Color cl1;
	for(int i=0;i<cwidth;i++)
	{
		for(int j=0;j<cheight;j++)
		{
			mas[i][j]=0;
		}
	}

	nobr=0;

	for(int i=0;i<cwidth;i++)
	{
		for(int j=0;j<cheight;j++)
		{			
			cl1 = cp->GetPixel(i,j);
			double bri = 1-((double)cl1.R/255);
			ms1[i][j] = bri;
			if((bri>=bri1)&&(mas[i][j]==0))
			{
				nobr++;
				marker(i,j);				
			}
		}
	}

	if(nobr==0)
	{
		MessageBox::Show("Не найдено ниодного образа!","ошибка");
		return;
	}
	if(nobr<(codelength-2))
	{
		MessageBox::Show("Слишком сильный шум","ошибка");
		return;
	}

	if (bboxes!=NULL)delete(bboxes);
	bboxes = new int * [nobr];
	for(int k=0;k<nobr;k++) bboxes[k] = new int[4];
	//порядок: x начало конец Y начало конец


	for(int k=0;k<nobr;k++)
	{
		int sx = 0;
		int fx = 0; 
		bboxes[k][0]=0; //здесь и далее это делается для того чтобы ящик был не пуст
		for(int i=0;i<cwidth;i++)
		{
			for(int j=0;j<cheight;j++)
			{
				if((sx==0)&&(mas[i][j]==k+1))
				{
					sx=1;
					bboxes[k][0]=i;
				}
				if(sx==1) break;
			}
			if(sx==1) break;
		}
		bboxes[k][1] = cwidth-1;
		for(int i=bboxes[k][0];i<cwidth;i++)
		{
			sx=0;
			for(int j=0;j<cheight;j++)
			{				
				if((sx==0)&&(mas[i][j]==k+1))
				{
					sx=1;
				}				
			}
			if (sx==0)
			{
				bboxes[k][1] = i-1;
				break;
			}
		}
		int sy = 0;
		int fy = 0;
		bboxes[k][2] = 0;
		for(int j=0;j<cheight;j++)
		{
			for(int i=0;i<cwidth;i++)
			{
				if((sy==0)&&(mas[i][j]==k+1))
				{
					sy=1;
					bboxes[k][2]=j;
				}				
			}		
		}
		bboxes[k][3] = cheight-1;
		for(int j=bboxes[k][2];j<cheight;j++)
		{
			sy=0;
			for(int i=0;i<cwidth;i++)
			{				
				if((sy==0)&&(mas[i][j]==k+1))
				{
					sy=1;
				}				
			}
			if (sy==0)
			{
				bboxes[k][3] = j-1;
				break;
			}
		}	
	}
	
	correctboxes();
}

void drawboxes(Graphics ^ g)
{
	//------------------------------------------------------------------
	//		Отображение рамок
	//------------------------------------------------------------------

	Color clr = System::Drawing::Color::Red;
	Pen ^ mypen = gcnew System::Drawing::Pen(clr);
	for(int k=0;k<nobr;k++)
	{
		g->DrawRectangle(mypen,bboxes[k][0],bboxes[k][2],bboxes[k][1]-bboxes[k][0],bboxes[k][3]-bboxes[k][2]);
	}
}

void adapt()
{
	//------------------------------------------------------------------
	//		Нормализация
	//------------------------------------------------------------------

	if(nobr==0)return;
	if(nobr<(codelength-2))return;
	//if(!checkarea())return;

	imgs = new double ** [nobr];
	for(int k=0;k<nobr;k++)
	{
		imgs[k] = new double * [dim];
		for(int i=0;i<dim;i++)
		{
			imgs[k][i] = new double [dim];
			for(int j=0;j<dim;j++)
			{
				imgs[k][i][j]=0;
			}

		}
	}
	//обнулили память таки...
	for(int k=0;k<nobr;k++)
	{
		//определить размеры
		int w = bboxes[k][1]-bboxes[k][0]+1;
		int h = bboxes[k][3]-bboxes[k][2]+1;
		double ** ma;
		int max;
		//определить что больше
		if(w>h)
		{			
			max = w;
			int raz = w-h;
			ma = new double * [w];
			for(int i=0;i<w;i++)
			{
				ma [i] = new double[w];
				for(int j=0;j<w;j++)
				{
					ma[i][j]=0;
					if(j<(raz/2))ma[i][j]=0;              //сначала пусто
					else if(j>(w-raz/2))ma[i][j]=0;       //вконце пусто
					else if (mas[i+bboxes[k][0]][j-raz/2+bboxes[k][2]]!=inds[k]+1)ma[i][j]=0; //если символ случайно откусили сбоку, то игнорируем
					else ma[i][j]=ms1[i+bboxes[k][0]][j-raz/2+bboxes[k][2]]; //посредине символ				
				}
			}
		}
		else if(h>w)
		{			
			max = h;
			int raz = h-w;
			ma = new double * [h];
			for(int i=0;i<h;i++)
			{
				ma[i] = new double[h];
				for(int j=0;j<h;j++)
				{
					ma[i][j]=0;
					if(i<(raz/2))ma[i][j]=0;              //сначала пусто
					else if(i>(h-raz/2))ma[i][j]=0;       //вконце пусто
					else if (mas[i-raz/2+bboxes[k][0]][j+bboxes[k][2]]!=(inds[k]+1))ma[i][j]=0;
					else ma[i][j]=ms1[i-raz/2+bboxes[k][0]][j+bboxes[k][2]]; //посредине символ	
					
				}
			}
		}
		else
		{			
		
			max = h;
			ma = new double * [h];
			for(int i=0;i<h;i++)
			{
				ma[i] = new double[h];
				for(int j=0;j<h;j++)
				{	
					ma[i][j]=0;
					if(mas[i+bboxes[k][0]][j+bboxes[k][2]]==(inds[k]+1))
						ma[i][j]=ms1[i+bboxes[k][0]][j+bboxes[k][2]];
				}
			}
		}
		
		//интерполяция линейная
		for(int i=0;i<dim*max;i++)
		{
			for(int j=0;j<dim*max;j++)
			{
				imgs[k][i/max][j/max]+=(double)(ma[i/dim][j/dim])/(double)(max*max);				
			}
		}
		
		/*for(int i=0;i<dim;i++)
		{
			for(int j=0;j<dim;j++)
			{
				log<<imgs[k][i][j]<<" ";
			}
			log<<endl;
		}
		log<<endl;
		log<<endl;
		//*/
	}
}


void ShowNormalized()
{
	//------------------------------------------------------------------
	//		Вывод нормализованных символов
	//------------------------------------------------------------------

	Bitmap ^ cp1 = gcnew Bitmap(cwidth,cheight);		

	for(int k=0;k<nobr;k++)
	{
		for(int i=0;i<dim;i++)
		{
			for(int j=0;j<dim;j++)
			{				
				int alf = (1-imgs[k][i][j])*255;
				if (alf>255) alf=255;
				if (alf<0) alf=0;				
				cp1->SetPixel(i+k*(dim+3),j,Color::FromArgb(255,alf,alf,alf));
			}
		}
	}
	pictureBox7->Image=cp1;
}

char doanalytics()
{
	//------------------------------------------------------------------
	//		Использование аналитических методов
	//------------------------------------------------------------------

	if(radioButton4->Checked)
	{
		int ans = dr->check(net->getouts());
		if(ans==777) 
		{
			textBox3->Text = String::Concat(textBox3->Text,gcnew String("*"));
			return 0;
		}
		else 
		{
			textBox3->Text = String::Concat(textBox3->Text,gcnew String(&liters[ans],0,1));
			return liters[ans];
		}
	}
	else if(radioButton5->Checked)
	{
		double r = (double)numericUpDown28->Value;
		int ans = dr->knear(net->getouts(),r);
		textBox3->Text = String::Concat(textBox3->Text,gcnew String(&liters[ans],0,1));
		return liters[ans];
	}	
}

char dostatistics(char ans1, char ans2)
{
	//------------------------------------------------------------------
	//		Использование статистики
	//------------------------------------------------------------------

	if(ans1==ans2)
	{
		textBox4->Text = String::Concat(textBox4->Text,gcnew String(&ans1,0,1));
		return ans1;
	}
	
	//если вероятность угадывания аналитикой того, что ответила сеть
	//больше, чем вероятность угадывания нейросетью того что ответила аналитика
	//то вернуть ответ аналитики.
	bool n = 0;
	double a1 = st->stats[literpos(ans1)];
	double a2 = st->stats[literpos(ans2)];
	double b1 = st->statsa[literpos(ans1)];
	double b2 = st->statsa[literpos(ans2)];

	if((a1>b1)&&(a2>b2)) n = 1;
	else if ((a1<=b1)&&(a2>b2)) n = 1;
	else n = 0;
	
	if(n==0)
	{
		textBox4->Text = String::Concat(textBox4->Text,gcnew String(&ans2,0,1));
		return ans2;
	}
	else
	{
		textBox4->Text = String::Concat(textBox4->Text,gcnew String(&ans1,0,1));
		return ans1;
	}
}

int literpos(char c)
{
	//------------------------------------------------------------------
	//		Позиция символа в массиве
	//------------------------------------------------------------------

	for(int i=0;i<numlit;i++)
	{
		if(liters[i]==c)return i;
	}
}

char * study()
{
	//------------------------------------------------------------------
	//		Обучение сети
	//------------------------------------------------------------------

	codelength = (int)numericUpDown1->Value;
	shperc = (float)numericUpDown5->Value/100;

	code = GenText();	
	textBox2->Clear();
	for(int j=0;j<codelength;j++)
	{
		textBox2->Text = String::Concat(textBox2->Text,gcnew String(&code[j],0,1));
	}
	//textBox2->Refresh();

	char * answer = new char[codelength];

	String ^ scode = gcnew  String(code,0,codelength);

	cp = gcnew Bitmap(cwidth,cheight);

	System::Drawing::Brush ^ cbrush = gcnew System::Drawing::SolidBrush(Color::Black); 
	g = System::Drawing::Graphics::FromImage(cp);
	g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);

	adnoise(g);

	System::Drawing::SizeF tesize = g->MeasureString( scode, cfont);//определить забариты строки
	int xpos = cwidth/2-tesize.Width/2; //строку поцентру
	int ypos = cheight/2-tesize.Height/2;
	
	MakeVertShifts(tesize.Height);			 
	
	MakeGorShifts(g);
	
	AddText(g, cbrush, xpos, ypos);
	
	remnoise();
	
	findletters();

	adapt();			 
	
	for(int i=0;i<nobr;i++)
	{
		char ans = net->learn(imgs[i],literpos(code[i]));		
		answer[i]=ans;
	}
	return answer;
}
void BlockControls()
{
	//------------------------------------------------------------------
	//		Блокировка управления
	//------------------------------------------------------------------

	 //button7->Visible=true;
	 button7->Enabled=true;
	 button1->Enabled=false;
	 button2->Enabled=false;
	 button3->Enabled=false;
	 button4->Enabled=false;
	 button5->Enabled=false;
	 button6->Enabled=false;
	 button10->Enabled=false;
	 button19->Enabled=false;
	 button21->Enabled=false;
}

void unBlockControls()
{
	//------------------------------------------------------------------
	//		Разблокировка управления
	//------------------------------------------------------------------

	 //button7->Visible=false;
	 button7->Enabled=false;			 
	 button1->Enabled=true;
	 button2->Enabled=true;
	 button3->Enabled=true;
	 button4->Enabled=true;
	 button5->Enabled=true;
	 button6->Enabled=true;
	 button10->Enabled=true;
	 button19->Enabled=true;
	 button21->Enabled=true;
}

char * GetNormalWord()
{
	//------------------------------------------------------------------
	//		Получение строки перебором
	//------------------------------------------------------------------

	 char * ans = new char[codelength];
	 for(int i=0;i<codelength;i++)
	 {
		 if (CurNInd==numlit) CurNInd=0;
		 ans[i]=liters[CurNInd];
		 CurNInd++;
	 }
	 return ans;
}

char * GetManualWord()
{
	//------------------------------------------------------------------
	//		Получение строки вручную
	//------------------------------------------------------------------

	char * ans = new char[codelength];
	int t = 0;
	for(int i=0;i<codelength;i++)
	{
		if (textBox2->Text->Length==0) ans[i]=liters[0]; // если ничо не ввели, берём первый из алфавита!
		else if(haslit(textBox2->Text[t])) //внимание! если символа нет, то берём первый из алфавита!
		ans[i]=textBox2->Text[t];
		else ans[i]=liters[0];

		t++;
		if(t==textBox2->Text->Length)t=0;
	}
	return ans;
}
char * GetRandomWord()
{
	//------------------------------------------------------------------
	//		Получение случайной строки
	//------------------------------------------------------------------

	char * ans = new char[codelength];
	Random ^ rd = gcnew Random();
	for(int i=0;i<codelength;i++)
	{
		int ln = rd->Next(numlit);
		ans[i]=liters[ln];
		
	}
	return ans;
}

bool haslit(char lit)
{
	//------------------------------------------------------------------
	//		Проверка наличия литеры
	//------------------------------------------------------------------

	for(int i=0;i<numlit;i++)
	{
		if(liters[i]==lit)return true;
	}
	return false;
}

void fillrows()
{
	//------------------------------------------------------------------
	//		Заполнение строк таблицы
	//------------------------------------------------------------------

	dataGridView1->Rows->Clear();
	dataGridView1->Rows->Add(numlit);
	for(int i=0;i<numlit;i++)
	{
		dataGridView1->Rows[i]->Cells[0]->Value = gcnew String(&liters[i],0,1); 
	}

}
void regrid(bool inad)
{
	//------------------------------------------------------------------
	//		Перезаполнение строк таблицы
	//------------------------------------------------------------------

	if(checkBox1->Checked==false)return;

	for(int i=0;i<numlit;i++)
	{
		dataGridView1->Rows[i]->DefaultCellStyle->BackColor=Color::White;
		dataGridView1->Rows[i]->Cells[1]->Value = st->laststats[i].ToString();
		dataGridView1->Rows[i]->Cells[2]->Value = st->stats[i].ToString();
		if(checkBox4->Checked)dataGridView1->Rows[i]->Cells[3]->Value = st->statsa[i].ToString();
		
		//if(st->laststats[i]>=st->crit)dataGridView1->Rows[i]->DefaultCellStyle->BackColor=Color::SpringGreen;
		//else if (inad) dataGridView1->Rows[i]->DefaultCellStyle->BackColor=Color::LightCoral;
	}
}
void drawings(Graphics ^ g)
{
	//------------------------------------------------------------------
	//		Рисование графика
	//------------------------------------------------------------------

	g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

	int sx = 0;
	int sy = 0;
	double scalex = (double)numericUpDown25->Value;
	double scaley = (double)numericUpDown26->Value;;

	Brush ^ br = gcnew SolidBrush(Color::White);
	Brush ^ br1 = gcnew SolidBrush(Color::Red);
	Brush ^ br2 = gcnew SolidBrush(Color::Green);
	Brush ^ br4 = gcnew SolidBrush(Color::Black);

	Pen ^ p = gcnew Pen(Color::Black,2);
	Pen ^ p1 = gcnew Pen(Color::LightGray);
	Pen ^ p2 = gcnew Pen(Color::Red,2);
	Pen ^ p3 = gcnew Pen(Color::Green,2);
	System::Drawing::Font^ f = gcnew System::Drawing::Font( "Arial",8 );

	//очистка
	g->FillRectangle(br,0,0,(numlit+3)*10*scalex,120*scaley);
	
	//вторичные оси
	for(int i=0;i<10;i++)
	{
		g->DrawLine(p1,(int)(10*scalex),(int)((1+i)*10*scaley),(int)((numlit+1)*10*scalex),(int)((1+i)*10*scaley));
	}
	for(int i=0;i<numlit;i++)
	{
		g->DrawLine(p1,(int)((2+i)*10*scalex),(int)(10*scaley),(int)((2+i)*10*scalex),(int)(110*scaley));
	}

	//оси
	g->DrawLine(p,10*scalex,0,10*scalex,110*scaley);
	g->DrawLine(p,10*scalex,0,8*scalex,5*scaley);
	g->DrawLine(p,10*scalex,0,12*scalex,5*scaley);

	g->DrawLine(p,(int)(10*scalex),(int)(110*scaley),(int)((numlit+2)*10*scalex),(int)(110*scaley));
	g->DrawLine(p,(int)((numlit+2)*10*scalex),(int)(110*scaley),(int)((numlit+2)*10*scalex-5*scalex),(int)(110*scaley-2*scaley));
	g->DrawLine(p,(int)((numlit+2)*10*scalex),(int)(110*scaley),(int)((numlit+2)*10*scalex-5*scalex),(int)(110*scaley+2*scaley));
			
	//пометки к осям
	for(int i=0;i<10;i++)
	{
		g->DrawString(((10-i)*10).ToString(),f,br4,2*scalex,(i+1)*10*scaley);
	}
	for(int i=0;i<numlit;i++)
	{
		g->DrawString(gcnew String(&liters[i],0,1),f,br4,(i+2)*10*scalex,110*scaley);
	}
	
	//собственно графики
	for(int i=0;i<numlit;i++)
	{
		int point = (st->stats[i]*100);
		g->FillEllipse(br1,(i+2)*10*scalex-3,(100-point+10)*scaley-3,6,6);

		if(checkBox4->Checked)
		{
			int point1 = (st->statsa[i]*100);
			g->FillEllipse(br2,(i+2)*10*scalex-3,(100-point1+10)*scaley-3,6,6);
			if(i>0)
			{
				int lastpoint1 = (st->statsa[i-1]*100);
				g->DrawLine(p3,(int)((i+1)*10*scalex),(int)((100-lastpoint1+10)*scaley),(int)((i+2)*10*scalex),(int)((100-point1+10)*scaley));				
			}
		}

		if(i>0)
		{
			int lastpoint = (st->stats[i-1]*100);
			g->DrawLine(p2,(int)((i+1)*10*scalex),(int)((100-lastpoint+10)*scaley),(int)((i+2)*10*scalex),(int)((100-point+10)*scaley));			
		}
	}
}
bool checkfin()
{
	//------------------------------------------------------------------
	//		Проверка останова
	//------------------------------------------------------------------

	int lastcodeletgth = codelength;
	codelength = 1;

	st->forcecheck();
	regrid(false);

	code = new char[1];
	char * ans = new char[1];

	for(int k=0;k<(int)numericUpDown11->Value;k++)
	{
		for(int i=0;i<numlit;i++)
		{
			code[0]=liters[i];
			ans[0] = singlepass();
			st->check(ans,code,1);
			log<<ans[0]<<" "<<code[0]<<endl;
		}
	}

	st->forcecheck();
	regrid(false);

	codelength = lastcodeletgth;
	
	if (st->winers==st->num) return 1;
	else return 0;
}

char singlepass()
{
	//------------------------------------------------------------------
	//		Единичный проход распознавания
	//------------------------------------------------------------------

	String ^ scode = gcnew  String(code,0,1);
	cp = gcnew Bitmap(cwidth,cheight);
	System::Drawing::Brush ^ cbrush = gcnew System::Drawing::SolidBrush(Color::Black); 
	g = System::Drawing::Graphics::FromImage(cp);
	g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);
	adnoise(g);
	System::Drawing::SizeF tesize = g->MeasureString( scode, cfont);//определить габариты строки
	int xpos = cwidth/2-tesize.Width/2; //строку поцентру
	int ypos = cheight/2-tesize.Height/2;
	MakeVertShifts(tesize.Height);			 
	MakeGorShifts(g);
	AddText(g, cbrush, xpos, ypos);
	remnoise();
	findletters();
	drawboxes(g);			 
	adapt();
	char ans = net->work(imgs[0]);

	return liters[ans];
}

char singlelearn()
{	
	//------------------------------------------------------------------
	//		Единичный проход обучения
	//------------------------------------------------------------------

	shperc = (float)numericUpDown5->Value/100;
	String ^ scode = gcnew  String(code,0,1);
	cp = gcnew Bitmap(cwidth,cheight);
	System::Drawing::Brush ^ cbrush = gcnew System::Drawing::SolidBrush(Color::Black); 
	g = System::Drawing::Graphics::FromImage(cp);
	g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);
	adnoise(g);
	System::Drawing::SizeF tesize = g->MeasureString( scode, cfont);//определить габариты строки
	int xpos = cwidth/2-tesize.Width/2; //строку поцентру
	int ypos = cheight/2-tesize.Height/2;
	MakeVertShifts(tesize.Height);			 
	MakeGorShifts(g);
	AddText(g, cbrush, xpos, ypos);
	remnoise();
	findletters();
	drawboxes(g);			 
	adapt();
	char ans = net->learn(imgs[0],literpos(code[0]));

	return liters[ans];
}

void advancedlearn()
{	
	//------------------------------------------------------------------
	//		Дообучение
	//------------------------------------------------------------------

	int lastcodeletgth = codelength;
	codelength = 1;

	code = new char[1];
	char * ans = new char[1];
	for(int i=0;i<numlit;i++)
	{
		if(st->laststats[i]<st->crit)
		{
			code[0]=liters[i];
			ans[0] = singlelearn();
			st->check(ans,code,1);
		}
	}

	codelength = lastcodeletgth;
}

void reinit()
{
	//------------------------------------------------------------------
	//		Инициализация начальными значениями
	//------------------------------------------------------------------

	delete(net);
	dim = (int)numericUpDown14->Value;
	dim2 = (int)numericUpDown29->Value;
	double w1 = (double)numericUpDown15->Value; //начальные веса от
	double w2 = (double)numericUpDown16->Value; //до
	double b1 = (double)numericUpDown17->Value; //пороги
	double b2 = (double)numericUpDown18->Value; //до
	double s1 = (double)numericUpDown4->Value;  //скорость обучения
	bool dl;
	if(checkBox3->Checked) 
	{
		dl=true;
		//listBox1->Enabled=false;
		//dataGridView2->Enabled=false;
	}
	else
	{
		dl=false;
		//listBox1->Enabled=true;
		//dataGridView2->Enabled=true;
	}

	net = new network(dim,dim,numlit,b1,b2,s1,w1,w2,dl,dim2);
	
	net->initialize();

	dataGridView2->Rows->Clear();
	dataGridView2->Columns->Clear();
	for(int i=0;i<dim;i++)
	{
		dataGridView2->Columns->Add(i.ToString(),i.ToString());
		dataGridView2->Columns[i]->Width = 35;

	}
	dataGridView2->Rows->Add(dim);
	for(int i=0;i<dim;i++)
	{
		dataGridView2->Rows[i]->HeaderCell->Value=i.ToString();
	}
}
void fillweightlist()
{
	//------------------------------------------------------------------
	//		Заполнение списка весов
	//------------------------------------------------------------------

	listBox1->Items->Clear();
	for(int i=0;i<numlit;i++)
	{
		listBox1->Items->Add(gcnew String(&liters[i],0,1));
	}
}
void fillweighttable(int n)
{
	//------------------------------------------------------------------
	//		Заполнение таблицы весов
	//------------------------------------------------------------------

	if(net->dl==true)
	{
		//fillweighttable2(n);
		return;
	}

	double min = net->x[0].w[0];
	double max = net->x[0].w[0];

	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{			
			dataGridView2->Rows[j]->Cells[i]->Value=net->x[i*dim+j].w[n];
			if(net->x[i*dim+j].w[n]<min)min=net->x[i*dim+j].w[n];
			if(net->x[i*dim+j].w[n]>max)max=net->x[i*dim+j].w[n];
		}
	}
	
	//цвета клеток

	double len = max-min;	
	unsigned char r;
	unsigned char g;
	unsigned char b;

	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{				
			if(net->x[i*dim+j].w[n]>0)
			{				
				g = 255;
				r=(1-(net->x[i*dim+j].w[n]/max))*255;
				b=(1-(net->x[i*dim+j].w[n]/max))*255;
			}
			else
			{
				g=(1-(net->x[i*dim+j].w[n]/min))*255;
				r = 255;
				b=(1-(net->x[i*dim+j].w[n]/min))*255;
			}			
			dataGridView2->Rows[j]->Cells[i]->Style->BackColor=Color::FromArgb(255,r,g,b);
		}
	}	
}
void fillweighttable2(int n)
{
	//------------------------------------------------------------------
	//		Не используется
	//------------------------------------------------------------------

	double min = net->nr[0].w[0];
	double max = net->nr[0].w[0];

	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{			
			dataGridView2->Rows[j]->Cells[i]->Value=net->nr[i*dim+j].w[n];
			if(net->nr[i*dim+j].w[n]<min)min=net->nr[i*dim+j].w[n];
			if(net->nr[i*dim+j].w[n]>max)max=net->nr[i*dim+j].w[n];
		}
	}
	
	//цвета клеток

	double len = max-min;	
	unsigned char r;
	unsigned char g;
	unsigned char b;

	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{				
			if(net->nr[i*dim+j].w[n]>0)
			{				
				g = 255;
				r=(1-(net->nr[i*dim+j].w[n]/max))*255;
				b=(1-(net->nr[i*dim+j].w[n]/max))*255;
			}
			else
			{
				g=(1-(net->nr[i*dim+j].w[n]/min))*255;
				r = 255;
				b=(1-(net->nr[i*dim+j].w[n]/min))*255;
			}			
			dataGridView2->Rows[j]->Cells[i]->Style->BackColor=Color::FromArgb(255,r,g,b);
		}
	}	
}

void fillfilterlist()
{
	//------------------------------------------------------------------
	//		Заполнение списка фильтров
	//------------------------------------------------------------------

	listBox2->Items->Clear();
	if(fl->head==NULL)return;

	filternode * temp = fl->head;
	while(temp!=NULL)
	{
		String ^ str;
		switch (temp->f->type)
		{
		case 0:
			{
				str  = String::Concat("Фильтр по весу пятна: вес=",temp->f->weight.ToString());
				break;
			}
		case 1:
			{
				str  = String::Concat("Фильтр по среднему: уровень=",temp->f->level.ToString()," радиус=",temp->f->rad.ToString());
				break;
			}
		case 2:
			{
				str  = String::Concat("Размытие по Гауссу: сигма=",temp->f->sigm.ToString()," радиус=",temp->f->rad.ToString());
				break;
			}
		case 3:
			{
				str  = String::Concat("Порог по яркости: уровень=",temp->f->brlev.ToString());
				break;
			}
		}
		listBox2->Items->Add(str);
		temp = temp->next;
	}
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if ( fontDialog1->ShowDialog() != System::Windows::Forms::DialogResult::Cancel )
			 {
				 cfont = fontDialog1->Font;
			 }
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 codelength = (int)numericUpDown1->Value;
			 shperc = (float)numericUpDown5->Value/100;

			 code = GenText();			 
			 textBox2->Clear();
			 for(int j=0;j<codelength;j++)
			 {
				 textBox2->Text = String::Concat(textBox2->Text,gcnew String(&code[j],0,1));
			 }
			 textBox2->Refresh();
			 String ^ scode = gcnew  String(code,0,codelength);

			 cp = gcnew Bitmap(cwidth,cheight);

			 System::Drawing::Brush ^ cbrush = gcnew System::Drawing::SolidBrush(Color::Black); 
			 g = System::Drawing::Graphics::FromImage(cp);
			 g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);


			 adnoise(g);

			 pictureBox1->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);

			 System::Drawing::SizeF tesize = g->MeasureString( scode, cfont);//определить забариты строки
			 int xpos = cwidth/2-tesize.Width/2; //строку поцентру
			 int ypos = cheight/2-tesize.Height/2;
			 MakeVertShifts(tesize.Height);			 
			 MakeGorShifts(g);
			 AddText(g, cbrush, xpos, ypos);
			 //g->DrawString(scode,cfont,cbrush,xpos,ypos);

			 pictureBox2->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);
			
			 cp12 = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);

			 PicCreated=true;
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(PicCreated==false)return;
			 PicCreated=false;

			 BlockControls();
			
			 pictureBox4->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);
			 remnoise();
			 pictureBox5->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);			 
			 findletters();

			 drawboxes(g);
			 
			 adapt();			 
			 pictureBox6->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);
			 ShowNormalized();

			 textBox1->Clear();		
			 textBox3->Clear();	
			 textBox4->Clear();	
			 for(int i=0;i<nobr;i++)
			 {
				 char ans = net->learn(imgs[i],literpos(code[i]));
				 textBox1->Text = String::Concat(textBox1->Text,gcnew String(&liters[ans],0,1));
				 //log<<liters[ans];
				 if(checkBox4->Checked) 
				 {
					 char ans2 = doanalytics();
					 if(checkBox5->Checked) dostatistics(liters[ans],ans2);
				 }
			 }
			 //log<<endl;

			 unBlockControls();
		 }


private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 BlockControls();

			 codelength = (int)numericUpDown1->Value;
			 shperc = (float)numericUpDown5->Value/100;

			 code = GenText();			 
			 textBox2->Clear();
			 for(int j=0;j<codelength;j++)
			 {
				 textBox2->Text = String::Concat(textBox2->Text,gcnew String(&code[j],0,1));
			 }
			 textBox2->Refresh();
			 String ^ scode = gcnew  String(code,0,codelength);

			 cp = gcnew Bitmap(cwidth,cheight);
			 
			 System::Drawing::Brush ^ cbrush = gcnew System::Drawing::SolidBrush(Color::Black); 
			 g = System::Drawing::Graphics::FromImage(cp);
			 g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);

			 adnoise(g);

			 pictureBox1->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);

			 System::Drawing::SizeF tesize = g->MeasureString( scode, cfont);//определить габариты строки
			 int xpos = cwidth/2-tesize.Width/2; //строку поцентру
			 int ypos = cheight/2-tesize.Height/2;
			 MakeVertShifts(tesize.Height);			 
			 MakeGorShifts(g);
			 AddText(g, cbrush, xpos, ypos);
			 //g->DrawString(scode,cfont,cbrush,xpos,ypos);

			 pictureBox2->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);

			 
			 pictureBox4->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);
			 remnoise();
			 pictureBox5->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);			 
			 findletters();

			 drawboxes(g);
			 
			 adapt();			 
			 pictureBox6->Image = cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);
			 ShowNormalized();

			 textBox1->Clear();	
			 textBox3->Clear();
			 textBox4->Clear();
			 for(int i=0;i<nobr;i++)
			 {
				 char ans = net->work(imgs[i]);
				 textBox1->Text = String::Concat(textBox1->Text,gcnew String(&liters[ans],0,1));

				 if(checkBox4->Checked) 
				 {
					 char ans2 = doanalytics();
					 if(checkBox5->Checked) dostatistics(liters[ans],ans2);
				 }

				 //log<<liters[ans];
			 }
			 //log<<endl;

			 unBlockControls();
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 BlockControls();
			 st->reset();
			 net->alef = (double)numericUpDown4->Value;
			 //DateTime dt1 = DateTime::Now;

			 double errnum = 0;
			 double errproc = 0;

			 for(int i=0;i<(int)numericUpDown6->Value;i++)
			 {				 
				 label18->Text=i.ToString();
				 char * ans = study();
				 textBox1->Clear();
				 for(int j=0;j<codelength;j++)
				 {
					 textBox1->Text = String::Concat(textBox1->Text,gcnew String(&liters[ans[j]],0,1));
					 if(liters[ans[j]]!=code[j]) errnum+=1;
				 }

				 st->check(code,ans);
				 st->checkstats();
				 regrid(false);

				 if((i%10)==0)
				 {
					 errproc = errnum/(codelength*10);
					 label20->Text=errproc.ToString("P2");					 
					 errnum=0;
				 }
				 
				 
				 
				 Application::DoEvents();
				 if(COMBOBREAKER){COMBOBREAKER=false; break;}
			 }
			 
			 //DateTime dt2 = DateTime::Now;
			 //label1->Text=((double)(dt2.Ticks-dt1.Ticks)).ToString();
			 label18->Text=" ";
			 unBlockControls();
		 }
private: System::Void panel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
		 {	
			 //полное обучение 

			 BlockControls();
			 st->reset();

			 net->alef = (double)numericUpDown4->Value;
			 double stalef = net->alef;
			 //DateTime dt1 = DateTime::Now;

			 double errnum = 0;
			 double errproc = 0;
			 int countz=0;
			 int i = 0;
			 char * anschars = new char[codelength];

			 while(1)
			 {		
				 i++;
				 label18->Text=i.ToString();
				 char * ans = study();
				 textBox1->Clear();
				 for(int j=0;j<codelength;j++)
				 {
					 textBox1->Text = String::Concat(textBox1->Text,gcnew String(&liters[ans[j]],0,1));
					 anschars[j]=liters[ans[j]];
					 if(liters[ans[j]]!=code[j]) errnum+=1;
				 }

				 st->check(anschars,code);
				 st->checkstats();				

				 if(((i*codelength)%((int)numericUpDown10->Value))==0)
				 {
					  regrid(false);
					 // предположительный останов ?

					 errproc = errnum/((int)numericUpDown10->Value);

					 if(errproc*100<=(int)numericUpDown7->Value)
					 {
						 if(checkfin())
						 {							 
							 break;
						 }
					 }

					 label20->Text=errproc.ToString("P2");
					 
					 errnum=0;
				 }

				 float minproc = ((float)numericUpDown12->Value)/100*numlit;
				 
				 if(st->winers>=minproc)
				 {
					 regrid(true);
					 Application::DoEvents();
					 advancedlearn();
				 }

				 if((i%100)==0)
				 {
					 //net->alef = stalef/(1 + (double)i/100);
					 net->alef = net->alef/2; // деление скорости пополам через каждые 500 образов. обучение за 3000 образов.
					 numericUpDown4->Value = (Decimal)net->alef;
					 
				 }

				 Application::DoEvents();
				 if(COMBOBREAKER){COMBOBREAKER=false; break;}
			 }

			 //DateTime dt2 = DateTime::Now;
			 //label1->Text=((double)(dt2.Ticks-dt1.Ticks)).ToString();
			 //label18->Text=" ";
			 unBlockControls();
		 }

		
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) 		 
		 {
			 COMBOBREAKER=true;
		 }
private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) 
		 {
		 }
private: System::Void numericUpDown8_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 st->setdiskr((int)numericUpDown8->Value);
		 }
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 st->setwordlength((int)numericUpDown1->Value);
		 }
private: System::Void numericUpDown7_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 st->setcrit(1-(float)numericUpDown7->Value/100);
		 }
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 codelength=1;
			 code = new char[1];
			 code[0] = 'a';
			 singlelearn();
			 pictureBox1->Image=cp->Clone(System::Drawing::Rectangle(0,0,cwidth,cheight),System::Drawing::Imaging::PixelFormat::DontCare);
		 }
private: System::Void numericUpDown4_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			  net->alef = (double)numericUpDown4->Value;
		 }
private: System::Void button8_Click_1(System::Object^  sender, System::EventArgs^  e) 
		 {
			 net->alef = net->alef/2;
			 numericUpDown4->Value=(Decimal)net->alef;
		 }
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 net->alef = net->alef*2;
			 numericUpDown4->Value=(Decimal)net->alef;
		 }
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 BlockControls();
			 
			 st->reset();
			 codelength = (int)numericUpDown1->Value;
			 shperc = (float)numericUpDown5->Value/100;
			 int tnum = (int)numericUpDown13->Value;
			 regrid(false);
			 char * anschars = new char[codelength];
			 char * anschars2 = new char[codelength];

			 for(int i=0;i<tnum;i++)
			 {
				 label18->Text=i.ToString();
				 code = GenText();			 
				 textBox2->Clear();
				 for(int j=0;j<codelength;j++)
				 {
					 textBox2->Text = String::Concat(textBox2->Text,gcnew String(&code[j],0,1));
				 }
				 textBox2->Refresh();
				 String ^ scode = gcnew  String(code,0,codelength);

				 cp = gcnew Bitmap(cwidth,cheight);
				 
				 System::Drawing::Brush ^ cbrush = gcnew System::Drawing::SolidBrush(Color::Black); 
				 g = System::Drawing::Graphics::FromImage(cp);
				 g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);
				 adnoise(g);
				 System::Drawing::SizeF tesize = g->MeasureString( scode, cfont);//определить габариты строки
				 int xpos = cwidth/2-tesize.Width/2; //строку поцентру
				 int ypos = cheight/2-tesize.Height/2;
				 MakeVertShifts(tesize.Height);			 
				 MakeGorShifts(g);
				 AddText(g, cbrush, xpos, ypos);
				 remnoise();
				 findletters();
				 drawboxes(g);
				 adapt();			 				 
				 textBox1->Clear();		
				 textBox3->Clear();	
				 textBox4->Clear();	
				 for(int i=0;i<nobr;i++)
				 {
					 char ans = net->work(imgs[i]);
					 textBox1->Text = String::Concat(textBox1->Text,gcnew String(&liters[ans],0,1));
					 anschars[i]=liters[ans];
					 
					 if(checkBox4->Checked) 
					 {
						 anschars2[i]=doanalytics();
						 if(checkBox5->Checked)
						 {
							 dostatistics(anschars[i],anschars2[i]);
						 }
					 }
				 }

				 if(!checkBox5->Checked) //если мы используем статистику в распознавании, мы не можем её править
				 {
					st->check(anschars,code);
					if(checkBox4->Checked)st->checka(anschars2,code);
					st->checkstats();
				 }
				 
				 Application::DoEvents();
				 if(COMBOBREAKER){COMBOBREAKER=false; break;}
				 
				 if(i%10==0)
				 {					
					regrid(false);
				 }
			 }	

			 regrid(false);
			 unBlockControls();
		 }
private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 reinit();
		 }
private: System::Void listBox1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {			 
			 fillweighttable((int)listBox1->SelectedIndex);
		 }
private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void numericUpDown3_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 filter * temp = new filter(0);
			 temp->cwidth = cwidth;
			 temp->cheight = cheight;
			 
			 noiseform ^ nf = gcnew noiseform(temp);
			 ::DialogResult dr = nf->ShowDialog();
			 if(dr==::DialogResult::OK)
			 {				 
				fl->add(temp);
				fillfilterlist();
			 }
		 }
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 fl->del((int)listBox2->SelectedIndex);
			 fillfilterlist();
		 }
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(listBox2->Items->Count==0)return;

			 int ind = (int)listBox2->SelectedIndex;
			 filter * temp = fl->get(ind);
			 
			 noiseform ^ nf = gcnew noiseform(temp);
			 ::DialogResult dr = nf->ShowDialog();
			 if(dr==::DialogResult::OK)
			 {				 
				fl->set(ind,temp);
				if(temp->type==2)temp->createpattern();
				fillfilterlist();
			 }
		 }
private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) 
		 {			 
			 int ind = (int)listBox2->SelectedIndex;
			 if(ind==0)return;
			 if(listBox2->Items->Count<=1)return;
			 fl->exchange(ind,ind-1);
			 fillfilterlist();
			 listBox2->SelectedIndex = ind-1;
		 }
private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 int ind = (int)listBox2->SelectedIndex;
			 int count = (int)listBox2->Items->Count;
			 if(listBox2->Items->Count<=1)return;
			 if(ind==count-1)return;
			 fl->exchange(ind,ind+1);
			 fillfilterlist();
			 listBox2->SelectedIndex = ind+1;
		 }
private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 net->save();
		 }
private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 ifstream ff1;
			 ff1.open("net.txt");
			 if(!ff1.is_open())
			 {
				 MessageBox::Show("Файл не найден","Ошибка");
			 }
			 else
			 {
				 ff1.close();
			 }
			 net->load();
			 numericUpDown14->Value = Decimal(Math::Sqrt(net->dim));
			 numericUpDown29->Value = net->dim2;
		 }
private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 BlockControls();
			 checkBox4->Enabled = false;
			 Application::DoEvents();

			 codelength = (int)numericUpDown1->Value;
			 shperc = (float)numericUpDown5->Value/100;
			 int tnum = (int)numericUpDown3->Value;			
			 char * anschars = new char[codelength];

			 dr = new dret(tnum*codelength);

			 for(int i=0;i<tnum;i++)
			 {
				 label47->Text=i.ToString();
				 code = GenText();

				 String ^ scode = gcnew  String(code,0,codelength);

				 cp = gcnew Bitmap(cwidth,cheight);

				 System::Drawing::Brush ^ cbrush = gcnew System::Drawing::SolidBrush(Color::Black);
				 g = System::Drawing::Graphics::FromImage(cp);
				 g->FillRectangle(System::Drawing::Brushes::White,0,0,cwidth,cheight);
				 adnoise(g);
				 System::Drawing::SizeF tesize = g->MeasureString( scode, cfont);//определить габариты строки
				 int xpos = cwidth/2-tesize.Width/2; //строку поцентру
				 int ypos = cheight/2-tesize.Height/2;
				 MakeVertShifts(tesize.Height);			 
				 MakeGorShifts(g);
				 AddText(g, cbrush, xpos, ypos);
				 remnoise();
				 findletters();
				 drawboxes(g);
				 adapt();

				 for(int i=0;i<nobr;i++)
				 {
					 char ans = net->work(imgs[i]);
					 
					 dr->add(net->getouts(),literpos(code[i]));
				 }				 

				 Application::DoEvents();
				 if(COMBOBREAKER){COMBOBREAKER=false; break;}				
			 }			 
			
			 checkBox4->Enabled = true;
			 unBlockControls();
		 }
private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 pictureBox3->Width=(double)numericUpDown25->Value * (numlit+3) * 10;
			 pictureBox3->Height=(double)numericUpDown26->Value * 120;

			 Bitmap ^ grb = gcnew Bitmap(pictureBox3->Width, pictureBox3->Height);
			 drawings(System::Drawing::Graphics::FromImage(grb));
			 pictureBox3->Image=grb;
		 }
private: System::Void panel4_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void button21_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 label52->Visible = true;
			 label52->Text = "Ожидайте...";
			 progressBar1->Value=0;
			 Application::DoEvents();

			 dr->premake();			 
			 for(int i=0;i<numlit;i++)
			 {
				dr->make(i);
				progressBar1->Value=i;
				Application::DoEvents();
			 }
			 progressBar1->Value=numlit;
			 label52->Text = "Готово!";			
		 }
};
}

