#include<iostream>
#include<string>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include"dirent.h"
#include"MyForm.h"

using namespace std;

string USBptr[4300];
string CDptr[130];
int USBSize;
int CDSize;
fstream file;

class Audio_Player
{
protected:
	string manufac_name;
	int model_no;
	bool Power;
public:
	Audio_Player(string manu_n = "", int mod_no = 0) :manufac_name(manu_n), model_no(mod_no), Power(0)
	{}
	virtual void PowerON() = 0;
	virtual void PowerOFF() = 0;
	virtual void setmanufac_name(string manu_n) = 0;
	virtual void setModel_no(int mod_no) = 0;
	virtual string getname() = 0;
	virtual	int getmodel_no() = 0;
	virtual string PlayMusicUSB() = 0;
	virtual string PlayMusicCD() = 0;
};

class StorageDevice
{
protected:
	bool Mounted;
	int CounterCD;
	int CounterUSB;
public:
	StorageDevice();
	void setmount(bool m);
	bool getmount();
	void setCounterCD(int k);
	int getCounterCD();
	void setCounterUSB(int k);
	int getCounterUSB();
	void CheckSize();
	void CheckFileType();
	void mounted();
	void UnMounted();
};
StorageDevice::StorageDevice() :Mounted(0), CounterCD(0), CounterUSB(0) {}
void StorageDevice::setmount(bool m)
{
	Mounted = m;
}
bool StorageDevice::getmount()
{
	return Mounted;
}
void StorageDevice::setCounterCD(int k) { CounterCD = k; }
int StorageDevice::getCounterCD() { return CounterCD; }
void StorageDevice::setCounterUSB(int k) { CounterUSB = k; }
int StorageDevice::getCounterUSB() { return CounterUSB; }
void StorageDevice::CheckSize()
{

}
void StorageDevice::CheckFileType()
{

}
void StorageDevice::mounted()
{
	Mounted = 1;
	CheckSize();
	CheckFileType();
}
void StorageDevice::UnMounted()
{
	Mounted = 0;
}

class In_Car_AP :public Audio_Player
{
	StorageDevice stdv;
public:
	In_Car_AP();
	void PowerON();
	void PowerOFF();
	void setmanufac_name(string manu_n);
	void setModel_no(int mod_no);
	string getname();
	int getmodel_no();
	string PlayMusicUSB();
	string PauseMusicUSB();
	string NextMusicUSB();
	string PreviousMusicUSB();
	string ShuffleUSB();
	void CloseMusicUSB();
	int GetIndexUSB(string);
	string PlayMusicCD();
	string PauseMusicCD();
	string NextMusicCD();
	string PreviousMusicCD();
	string ShuffleCD();
	void CloseMusicCD();
	int GetIndexCD(string);
	void RandomPlay(int);
};
In_Car_AP::In_Car_AP() {}
void In_Car_AP::PowerON()
{
	Power = 1;
}
void In_Car_AP::PowerOFF()
{
	Power = 0;
}
void In_Car_AP::setmanufac_name(string manu_n)
{
	manufac_name = manu_n;
}
void In_Car_AP::setModel_no(int mod_no)
{
	model_no = mod_no;
}
string In_Car_AP::getname()
{
	return manufac_name;
}
int In_Car_AP::getmodel_no()
{
	return model_no;
}
string In_Car_AP::PlayMusicUSB()
{
	string str = USBptr[stdv.getCounterUSB()] + " is Playing Now!!";
	//ptr[stdv.getCounter()] << " is Playing Now!!\n\n";
	string cmd = "play .\\USB\\" + USBptr[stdv.getCounterUSB()];
	mciSendStringA(cmd.c_str(), NULL, 0, NULL);
	return str;
}
string In_Car_AP::PauseMusicUSB()
{
	string str = USBptr[stdv.getCounterUSB()] + " is Paused Now!!";
	string cmd = "pause .\\USB\\" + USBptr[stdv.getCounterUSB()];
	mciSendStringA(cmd.c_str(), NULL, 0, NULL);
	return str;
}
string In_Car_AP::NextMusicUSB()
{
	CloseMusicUSB();
	if (stdv.getCounterUSB() >= (USBSize - 1))
	{
		string s = PlayMusicUSB();
		return s;
	}
	else
	{
		stdv.setCounterUSB(stdv.getCounterUSB() + 1);
		string s = PlayMusicUSB();
		return s;
	}
}
string In_Car_AP::PreviousMusicUSB()
{
	CloseMusicUSB();
	if (stdv.getCounterUSB() <= 0)
	{
		string s = PlayMusicUSB();
		return s;
	}
	else
	{
		stdv.setCounterUSB(stdv.getCounterUSB() - 1);
		string s = PlayMusicUSB();
		return s;
	}
}
string In_Car_AP::ShuffleUSB()
{
	CloseMusicUSB();
	stdv.setCounterUSB(rand() % USBSize);
	string s = PlayMusicUSB();
	return s;
}
void In_Car_AP::CloseMusicUSB()
{
	string cmd = "close .\\USB\\" + USBptr[stdv.getCounterUSB()];
	mciSendStringA(cmd.c_str(), NULL, 0, NULL);
}
int In_Car_AP::GetIndexUSB(string s)
{
	string onlyname = s.substr(0, s.length() - 17);
	for (int i = 0; i < USBSize; i++)
	{
		if (onlyname == USBptr[i])
		{
			return i;
		}
	}
}

string In_Car_AP::PlayMusicCD()
{
	string str = CDptr[stdv.getCounterCD()] + " is Playing Now!!";
	//cout << endl << ptr[stdv.getCounter()] << " is Playing Now!!\n\n";
	string cmd = "play .\\CD\\" + CDptr[stdv.getCounterCD()];
	mciSendStringA(cmd.c_str(), NULL, 0, NULL);
	return str;
}
string In_Car_AP::PauseMusicCD()
{
	string str = CDptr[stdv.getCounterCD()] + " is Paused Now!!";
	string cmd = "pause .\\CD\\" + CDptr[stdv.getCounterCD()];
	mciSendStringA(cmd.c_str(), NULL, 0, NULL);
	return str;
}
string In_Car_AP::NextMusicCD()
{
	CloseMusicCD();
	if (stdv.getCounterCD() >= (CDSize - 1))
	{
		string s = PlayMusicCD();
		return s;
	}
	else
	{
		stdv.setCounterCD(stdv.getCounterCD() + 1);
		string s = PlayMusicCD();
		return s;
	}
}
string In_Car_AP::PreviousMusicCD()
{
	CloseMusicCD();
	if (stdv.getCounterCD() <= 0)
	{
		string s = PlayMusicCD();
		return s;
	}
	else
	{
		stdv.setCounterCD(stdv.getCounterCD() - 1);
		string s = PlayMusicCD();
		return s;
	}
}
string In_Car_AP::ShuffleCD()
{
	CloseMusicCD();
	stdv.setCounterCD(rand() % CDSize);
	string s = PlayMusicCD();
	return s;
}
void In_Car_AP::CloseMusicCD()
{
	string cmd = "close .\\CD\\" + CDptr[stdv.getCounterCD()];
	mciSendStringA(cmd.c_str(), NULL, 0, NULL);
}
int In_Car_AP::GetIndexCD(string s)
{
	string onlyname = s.substr(0, s.length() - 17);
	for (int i = 0; i < CDSize; i++)
	{
		if (onlyname == CDptr[i])
		{
			return i;
		}
	}
}
void In_Car_AP::RandomPlay(int index)
{
}

class USB :public StorageDevice
{
public:
	USB();
	void opencloseUSB();
	string PlayListUSB();
	void SavePlayListUSB();
};
USB::USB() {}
void USB::opencloseUSB()
{
	int size = 0;
	string path2 = "./USB";
	DIR* dirusb = opendir(path2.c_str());
	struct dirent* entity2 = NULL;
	//cout << "******USB Directry******\n";
	while (entity2 = readdir(dirusb))
	{
		string usb = entity2->d_name;
		if (usb.length() > 4)
		{
			string s2 = usb.substr(usb.length() - 4, usb.length());
			if (s2 == ".mp3")
			{
				//cout << (size + 1) << ") " << entity2->d_name << endl;
				USBptr[size] = usb;
				size++;
				if ((size - 1) > 4300)
				{
					//cout << "Error!USB Storage exceeded the limit\n";
				}
			}
		}
	}
	USBSize = size;
	closedir(dirusb);
}
string USB::PlayListUSB()
{
	static int i = 0;
	if (i < USBSize)
	{
		if (i == (USBSize - 1))
		{
			i = 0;
			return USBptr[USBSize - 1];
		}
		i++;
		return USBptr[i - 1];
	}
}
void USB::SavePlayListUSB()
{
	file.open("PlayList.txt", ios::out | ios::app);
	file << "\n\n*****USB PlayList*****\n";
	for (int i = 0; i < USBSize; i++)
	{
		file << (i + 1) << ") " << USBptr[i] << endl;
	}
	file.close();
}

class CD :public StorageDevice
{
public:
	void openCD();
	string PlayListCD();
	void SavePlayListCD();
};
void CD::openCD()
{
	int size = 0;
	string path = "./CD";
	DIR* dircd = opendir(path.c_str());
	struct dirent* entity = NULL;
	//cout << "******CD Directry******\n";
	while (entity = readdir(dircd))
	{
		string cd = entity->d_name;
		if (cd.length() > 4)
		{
			string s1 = cd.substr(cd.length() - 4, cd.length());
			if (s1 == ".mp3")
			{
				//cout << (size + 1) << ") " << entity->d_name << endl;
				CDptr[size] = cd;
				size++;
				if ((size - 1) > 130)
				{
					//cout << "Error!CD Storage exceeded the limit\n";
				}
			}
		}
	}
	CDSize = size;
	closedir(dircd);
}
string CD::PlayListCD()
{
	static int i = 0;
	if (i < CDSize)
	{
		if (i == (CDSize - 1))
		{
			i = 0;
			return CDptr[CDSize - 1];
		}
		i++;
		return CDptr[i - 1];
	}
}
void CD::SavePlayListCD()
{
	file.open("PlayList.txt", ios::out | ios::app);
	file << "*****CD PlayList*****\n";
	for (int i = 0; i < CDSize; i++)
	{
		file << (i + 1) << ") " << CDptr[i] << endl;
	}
	file.close();
}





*******GUIFORMCODE********

#pragma once
#include"Header.h"

In_Car_AP ap;

namespace GUIOFAssignment01 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ PowerButton;
	private: System::Windows::Forms::RadioButton^ ONButton;
	private: System::Windows::Forms::RadioButton^ OFFButton;
	private: System::Windows::Forms::TextBox^ NameTitleBox;


	protected:

	protected:









	private: System::Windows::Forms::RadioButton^ USBButton;

	private: System::Windows::Forms::RadioButton^ CDButton;
	private: System::Windows::Forms::RadioButton^ UnMounted;


	private: System::Windows::Forms::RadioButton^ Mounted;

	private: System::Windows::Forms::ListBox^ PlayList;
	private: System::Windows::Forms::TextBox^ PlayingSongBox;
	private: System::Windows::Forms::TextBox^ CompanyModelTextBox;




	private: System::Windows::Forms::PictureBox^ PreviousButton;

	private: System::Windows::Forms::PictureBox^ NextButton;
	private: System::Windows::Forms::PictureBox^ PlayButton;




	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::PictureBox^ MountButton;
	private: System::Windows::Forms::PictureBox^ PauseButton;


	private: System::Windows::Forms::RadioButton^ IsPlaying;



	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Timer^ Time;
	private: System::Windows::Forms::Label^ SearchLabel;
	private: System::Windows::Forms::TextBox^ SearchTextBox;
	private: System::Windows::Forms::PictureBox^ SearchButton;

	private: System::Windows::Forms::PictureBox^ ShuffleButton;






	private: System::ComponentModel::IContainer^ components;




	protected:


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->PowerButton = (gcnew System::Windows::Forms::PictureBox());
			this->ONButton = (gcnew System::Windows::Forms::RadioButton());
			this->OFFButton = (gcnew System::Windows::Forms::RadioButton());
			this->NameTitleBox = (gcnew System::Windows::Forms::TextBox());
			this->USBButton = (gcnew System::Windows::Forms::RadioButton());
			this->CDButton = (gcnew System::Windows::Forms::RadioButton());
			this->UnMounted = (gcnew System::Windows::Forms::RadioButton());
			this->Mounted = (gcnew System::Windows::Forms::RadioButton());
			this->PlayList = (gcnew System::Windows::Forms::ListBox());
			this->PlayingSongBox = (gcnew System::Windows::Forms::TextBox());
			this->CompanyModelTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PreviousButton = (gcnew System::Windows::Forms::PictureBox());
			this->NextButton = (gcnew System::Windows::Forms::PictureBox());
			this->PlayButton = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->MountButton = (gcnew System::Windows::Forms::PictureBox());
			this->PauseButton = (gcnew System::Windows::Forms::PictureBox());
			this->IsPlaying = (gcnew System::Windows::Forms::RadioButton());
			this->Time = (gcnew System::Windows::Forms::Timer(this->components));
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->SearchLabel = (gcnew System::Windows::Forms::Label());
			this->SearchTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SearchButton = (gcnew System::Windows::Forms::PictureBox());
			this->ShuffleButton = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PowerButton))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PreviousButton))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NextButton))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PlayButton))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MountButton))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PauseButton))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SearchButton))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ShuffleButton))->BeginInit();
			this->SuspendLayout();
			// 
			// PowerButton
			// 
			this->PowerButton->BackColor = System::Drawing::Color::Transparent;
			this->PowerButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PowerButton.Image")));
			this->PowerButton->Location = System::Drawing::Point(12, 61);
			this->PowerButton->Name = L"PowerButton";
			this->PowerButton->Size = System::Drawing::Size(57, 55);
			this->PowerButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PowerButton->TabIndex = 5;
			this->PowerButton->TabStop = false;
			this->PowerButton->Click += gcnew System::EventHandler(this, &MyForm::PowerButton_Click);
			// 
			// ONButton
			// 
			this->ONButton->AutoCheck = false;
			this->ONButton->AutoSize = true;
			this->ONButton->BackColor = System::Drawing::Color::Transparent;
			this->ONButton->ForeColor = System::Drawing::Color::Pink;
			this->ONButton->Location = System::Drawing::Point(4, 11);
			this->ONButton->Name = L"ONButton";
			this->ONButton->Size = System::Drawing::Size(50, 21);
			this->ONButton->TabIndex = 6;
			this->ONButton->Text = L"ON";
			this->ONButton->UseVisualStyleBackColor = false;
			this->ONButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::ONButton_CheckedChanged);
			// 
			// OFFButton
			// 
			this->OFFButton->AutoCheck = false;
			this->OFFButton->AutoSize = true;
			this->OFFButton->BackColor = System::Drawing::Color::Transparent;
			this->OFFButton->Checked = true;
			this->OFFButton->ForeColor = System::Drawing::Color::Pink;
			this->OFFButton->Location = System::Drawing::Point(69, 11);
			this->OFFButton->Name = L"OFFButton";
			this->OFFButton->Size = System::Drawing::Size(56, 21);
			this->OFFButton->TabIndex = 7;
			this->OFFButton->TabStop = true;
			this->OFFButton->Text = L"OFF";
			this->OFFButton->UseVisualStyleBackColor = false;
			this->OFFButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::RadioButton2_CheckedChanged);
			// 
			// NameTitleBox
			// 
			this->NameTitleBox->BackColor = System::Drawing::Color::MidnightBlue;
			this->NameTitleBox->Cursor = System::Windows::Forms::Cursors::No;
			this->NameTitleBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NameTitleBox->ForeColor = System::Drawing::Color::Pink;
			this->NameTitleBox->Location = System::Drawing::Point(217, 0);
			this->NameTitleBox->Name = L"NameTitleBox";
			this->NameTitleBox->Size = System::Drawing::Size(242, 34);
			this->NameTitleBox->TabIndex = 8;
			this->NameTitleBox->Text = L"In-Car Audio-Player";
			this->NameTitleBox->TextChanged += gcnew System::EventHandler(this, &MyForm::c);
			// 
			// USBButton
			// 
			this->USBButton->AutoCheck = false;
			this->USBButton->AutoSize = true;
			this->USBButton->ForeColor = System::Drawing::Color::Pink;
			this->USBButton->Location = System::Drawing::Point(96, 17);
			this->USBButton->Name = L"USBButton";
			this->USBButton->Size = System::Drawing::Size(57, 21);
			this->USBButton->TabIndex = 9;
			this->USBButton->Text = L"USB";
			this->USBButton->UseVisualStyleBackColor = true;
			this->USBButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::USBButton_CheckedChanged);
			// 
			// CDButton
			// 
			this->CDButton->AutoCheck = false;
			this->CDButton->AutoSize = true;
			this->CDButton->ForeColor = System::Drawing::Color::Pink;
			this->CDButton->Location = System::Drawing::Point(6, 17);
			this->CDButton->Name = L"CDButton";
			this->CDButton->Size = System::Drawing::Size(48, 21);
			this->CDButton->TabIndex = 10;
			this->CDButton->Text = L"CD";
			this->CDButton->UseVisualStyleBackColor = true;
			this->CDButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::CDButton_CheckedChanged);
			// 
			// UnMounted
			// 
			this->UnMounted->AutoCheck = false;
			this->UnMounted->AutoSize = true;
			this->UnMounted->ForeColor = System::Drawing::Color::Pink;
			this->UnMounted->Location = System::Drawing::Point(6, 40);
			this->UnMounted->Name = L"UnMounted";
			this->UnMounted->Size = System::Drawing::Size(102, 21);
			this->UnMounted->TabIndex = 11;
			this->UnMounted->Text = L"UnMounted";
			this->UnMounted->UseVisualStyleBackColor = true;
			// 
			// Mounted
			// 
			this->Mounted->AutoCheck = false;
			this->Mounted->AutoSize = true;
			this->Mounted->ForeColor = System::Drawing::Color::Pink;
			this->Mounted->Location = System::Drawing::Point(6, 13);
			this->Mounted->Name = L"Mounted";
			this->Mounted->Size = System::Drawing::Size(84, 21);
			this->Mounted->TabIndex = 12;
			this->Mounted->Text = L"Mounted";
			this->Mounted->UseVisualStyleBackColor = true;
			this->Mounted->CheckedChanged += gcnew System::EventHandler(this, &MyForm::Mounted_CheckedChanged);
			// 
			// PlayList
			// 
			this->PlayList->BackColor = System::Drawing::Color::MidnightBlue;
			this->PlayList->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PlayList->ForeColor = System::Drawing::Color::Pink;
			this->PlayList->FormattingEnabled = true;
			this->PlayList->HorizontalScrollbar = true;
			this->PlayList->ItemHeight = 17;
			this->PlayList->Location = System::Drawing::Point(457, 232);
			this->PlayList->Name = L"PlayList";
			this->PlayList->Size = System::Drawing::Size(223, 242);
			this->PlayList->TabIndex = 13;
			this->PlayList->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// PlayingSongBox
			// 
			this->PlayingSongBox->BackColor = System::Drawing::Color::MidnightBlue;
			this->PlayingSongBox->Cursor = System::Windows::Forms::Cursors::No;
			this->PlayingSongBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PlayingSongBox->ForeColor = System::Drawing::Color::Pink;
			this->PlayingSongBox->Location = System::Drawing::Point(98, 169);
			this->PlayingSongBox->Name = L"PlayingSongBox";
			this->PlayingSongBox->Size = System::Drawing::Size(375, 27);
			this->PlayingSongBox->TabIndex = 14;
			this->PlayingSongBox->TextChanged += gcnew System::EventHandler(this, &MyForm::PlayingSongBox_TextChanged_2);
			// 
			// CompanyModelTextBox
			// 
			this->CompanyModelTextBox->BackColor = System::Drawing::SystemColors::HotTrack;
			this->CompanyModelTextBox->Cursor = System::Windows::Forms::Cursors::No;
			this->CompanyModelTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->CompanyModelTextBox->Location = System::Drawing::Point(12, 488);
			this->CompanyModelTextBox->Name = L"CompanyModelTextBox";
			this->CompanyModelTextBox->Size = System::Drawing::Size(164, 27);
			this->CompanyModelTextBox->TabIndex = 15;
			this->CompanyModelTextBox->Text = L"Audionic/2010";
			this->CompanyModelTextBox->TextChanged += gcnew System::EventHandler(this, &MyForm::CompanyModelTextBox_TextChanged);
			// 
			// PreviousButton
			// 
			this->PreviousButton->BackColor = System::Drawing::Color::Transparent;
			this->PreviousButton->Enabled = false;
			this->PreviousButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PreviousButton.Image")));
			this->PreviousButton->Location = System::Drawing::Point(156, 359);
			this->PreviousButton->Name = L"PreviousButton";
			this->PreviousButton->Size = System::Drawing::Size(56, 50);
			this->PreviousButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PreviousButton->TabIndex = 16;
			this->PreviousButton->TabStop = false;
			this->PreviousButton->Click += gcnew System::EventHandler(this, &MyForm::PreviousButton_Click);
			// 
			// NextButton
			// 
			this->NextButton->BackColor = System::Drawing::Color::Transparent;
			this->NextButton->Enabled = false;
			this->NextButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"NextButton.Image")));
			this->NextButton->Location = System::Drawing::Point(327, 359);
			this->NextButton->Name = L"NextButton";
			this->NextButton->Size = System::Drawing::Size(52, 50);
			this->NextButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->NextButton->TabIndex = 17;
			this->NextButton->TabStop = false;
			this->NextButton->Click += gcnew System::EventHandler(this, &MyForm::NextButton_Click);
			// 
			// PlayButton
			// 
			this->PlayButton->BackColor = System::Drawing::Color::Transparent;
			this->PlayButton->Enabled = false;
			this->PlayButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PlayButton.Image")));
			this->PlayButton->Location = System::Drawing::Point(227, 351);
			this->PlayButton->Name = L"PlayButton";
			this->PlayButton->Size = System::Drawing::Size(82, 68);
			this->PlayButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PlayButton->TabIndex = 18;
			this->PlayButton->TabStop = false;
			this->PlayButton->Click += gcnew System::EventHandler(this, &MyForm::PlayButton_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->Controls->Add(this->OFFButton);
			this->groupBox1->Controls->Add(this->ONButton);
			this->groupBox1->Cursor = System::Windows::Forms::Cursors::PanNW;
			this->groupBox1->Location = System::Drawing::Point(87, 61);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(142, 38);
			this->groupBox1->TabIndex = 19;
			this->groupBox1->TabStop = false;
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			this->groupBox2->Controls->Add(this->USBButton);
			this->groupBox2->Controls->Add(this->CDButton);
			this->groupBox2->Location = System::Drawing::Point(486, 40);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(155, 53);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Enter += gcnew System::EventHandler(this, &MyForm::groupBox2_Enter);
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::Transparent;
			this->groupBox3->Controls->Add(this->UnMounted);
			this->groupBox3->Controls->Add(this->Mounted);
			this->groupBox3->Location = System::Drawing::Point(571, 101);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(109, 74);
			this->groupBox3->TabIndex = 0;
			this->groupBox3->TabStop = false;
			this->groupBox3->Enter += gcnew System::EventHandler(this, &MyForm::groupBox3_Enter);
			// 
			// MountButton
			// 
			this->MountButton->BackColor = System::Drawing::Color::Transparent;
			this->MountButton->Enabled = false;
			this->MountButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"MountButton.Image")));
			this->MountButton->Location = System::Drawing::Point(415, 40);
			this->MountButton->Name = L"MountButton";
			this->MountButton->Size = System::Drawing::Size(65, 55);
			this->MountButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->MountButton->TabIndex = 20;
			this->MountButton->TabStop = false;
			this->MountButton->Click += gcnew System::EventHandler(this, &MyForm::MountButton_Click);
			// 
			// PauseButton
			// 
			this->PauseButton->BackColor = System::Drawing::Color::Transparent;
			this->PauseButton->Enabled = false;
			this->PauseButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PauseButton.Image")));
			this->PauseButton->Location = System::Drawing::Point(227, 351);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(82, 68);
			this->PauseButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PauseButton->TabIndex = 21;
			this->PauseButton->TabStop = false;
			this->PauseButton->Visible = false;
			this->PauseButton->Click += gcnew System::EventHandler(this, &MyForm::PauseButton_Click);
			// 
			// IsPlaying
			// 
			this->IsPlaying->AutoCheck = false;
			this->IsPlaying->AutoSize = true;
			this->IsPlaying->BackColor = System::Drawing::Color::Transparent;
			this->IsPlaying->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IsPlaying->ForeColor = System::Drawing::Color::Pink;
			this->IsPlaying->Location = System::Drawing::Point(195, 197);
			this->IsPlaying->Name = L"IsPlaying";
			this->IsPlaying->Size = System::Drawing::Size(184, 29);
			this->IsPlaying->TabIndex = 23;
			this->IsPlaying->TabStop = true;
			this->IsPlaying->Text = L"SoundIsPlaying";
			this->IsPlaying->UseVisualStyleBackColor = false;
			this->IsPlaying->CheckedChanged += gcnew System::EventHandler(this, &MyForm::IsPlaying_CheckedChanged);
			// 
			// Time
			// 
			this->Time->Enabled = true;
			this->Time->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(156, 293);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(223, 23);
			this->progressBar1->Step = 1;
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar1->TabIndex = 24;
			this->progressBar1->Click += gcnew System::EventHandler(this, &MyForm::progressBar1_Click);
			// 
			// SearchLabel
			// 
			this->SearchLabel->AutoSize = true;
			this->SearchLabel->BackColor = System::Drawing::Color::Transparent;
			this->SearchLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SearchLabel->ForeColor = System::Drawing::Color::Pink;
			this->SearchLabel->Location = System::Drawing::Point(454, 211);
			this->SearchLabel->Name = L"SearchLabel";
			this->SearchLabel->Size = System::Drawing::Size(66, 18);
			this->SearchLabel->TabIndex = 25;
			this->SearchLabel->Text = L"Search:";
			this->SearchLabel->Click += gcnew System::EventHandler(this, &MyForm::SearchLabel_Click);
			// 
			// SearchTextBox
			// 
			this->SearchTextBox->BackColor = System::Drawing::Color::MidnightBlue;
			this->SearchTextBox->ForeColor = System::Drawing::Color::Pink;
			this->SearchTextBox->Location = System::Drawing::Point(517, 211);
			this->SearchTextBox->Name = L"SearchTextBox";
			this->SearchTextBox->Size = System::Drawing::Size(124, 22);
			this->SearchTextBox->TabIndex = 26;
			// 
			// SearchButton
			// 
			this->SearchButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SearchButton.Image")));
			this->SearchButton->Location = System::Drawing::Point(646, 208);
			this->SearchButton->Name = L"SearchButton";
			this->SearchButton->Size = System::Drawing::Size(33, 25);
			this->SearchButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->SearchButton->TabIndex = 27;
			this->SearchButton->TabStop = false;
			this->SearchButton->Click += gcnew System::EventHandler(this, &MyForm::SearchButton_Click);
			// 
			// ShuffleButton
			// 
			this->ShuffleButton->Enabled = false;
			this->ShuffleButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ShuffleButton.Image")));
			this->ShuffleButton->Location = System::Drawing::Point(236, 424);
			this->ShuffleButton->Name = L"ShuffleButton";
			this->ShuffleButton->Size = System::Drawing::Size(62, 50);
			this->ShuffleButton->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->ShuffleButton->TabIndex = 28;
			this->ShuffleButton->TabStop = false;
			this->ShuffleButton->Click += gcnew System::EventHandler(this, &MyForm::ShuffleButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(692, 523);
			this->Controls->Add(this->ShuffleButton);
			this->Controls->Add(this->SearchButton);
			this->Controls->Add(this->SearchTextBox);
			this->Controls->Add(this->SearchLabel);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->IsPlaying);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->MountButton);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->PlayButton);
			this->Controls->Add(this->NextButton);
			this->Controls->Add(this->PreviousButton);
			this->Controls->Add(this->CompanyModelTextBox);
			this->Controls->Add(this->PlayingSongBox);
			this->Controls->Add(this->PlayList);
			this->Controls->Add(this->NameTitleBox);
			this->Controls->Add(this->PowerButton);
			this->Cursor = System::Windows::Forms::Cursors::PanNW;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Click += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PowerButton))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PreviousButton))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NextButton))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PlayButton))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->MountButton))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PauseButton))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SearchButton))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ShuffleButton))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}



	private: System::Void PowerButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (OFFButton->Checked == true)
		{
			MountButton->Enabled = true;
			OFFButton->Checked = false;
			ONButton->Checked = true;
			UnMounted->Checked = true;
			if (USBButton->Checked == true || CDButton->Checked == true)
			{
				IsPlaying->Checked = true;
				Mounted->Checked = true;
				UnMounted->Checked = false;
				if (USBButton->Checked == true)
				{
					string s = ap.PlayMusicUSB();
					String^ str2 = gcnew String(s.c_str());
					PlayingSongBox->Text = str2;
				}
				else if (CDButton->Checked == true)
				{
					string s = ap.PlayMusicCD();
					String^ str2 = gcnew String(s.c_str());
					PlayingSongBox->Text = str2;

				}
				PlayButton->Enabled = true;
				PauseButton->Enabled = true;
				NextButton->Enabled = true;
				PreviousButton->Enabled = true;

			}
		}
		else if (ONButton->Checked == true)
		{
			OFFButton->Checked = true;
			ONButton->Checked = false;
			UnMounted->Checked = false;
			Mounted->Checked = false;
			IsPlaying->Checked = false;
			PlayButton->Enabled = false;
			PauseButton->Enabled = false;
			PreviousButton->Enabled = false;
			NextButton->Enabled = false;
			if (USBButton->Checked == true)
			{
				ap.CloseMusicUSB();
			}
			else if (CDButton->Checked == true)
			{
				ap.CloseMusicCD();
			}
		}
	}
	private: System::Void RadioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void PreviousButton_Click(System::Object^ sender, System::EventArgs^ e) {
		PauseButton->Visible = true;
		PlayButton->Visible = false;
		if (USBButton->Checked == true)
		{
			string s = ap.PreviousMusicUSB();
			String^ str2 = gcnew String(s.c_str());
			PlayingSongBox->Text = str2;
			PlayList->SetSelected(ap.GetIndexUSB(s), true);
		}
		else if (CDButton->Checked == true)
		{
			string s = ap.PreviousMusicCD();
			String^ str2 = gcnew String(s.c_str());
			PlayingSongBox->Text = str2;
			PlayList->SetSelected(ap.GetIndexCD(s), true);
		}
	}
	private: System::Void groupBox2_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox3_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void Mounted_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ONButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		//if (ONButton->Checked == true)
		//{
		//	ONButton->Enabled = true;
		//	USBButton->Enabled = true;
		//	CDButton->Enabled = true;
		//	UnMounted->Enabled = true;
		//	Mounted->Enabled = true;
		//}
	}
	private: System::Void CDButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (ONButton->Checked == true)
		{
			if (CDButton->Checked == true)
			{
				UnMounted->Checked = false;
				Mounted->Checked = true;
			}
		}
	}
	private: System::Void USBButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (ONButton->Checked == true)
		{
			if (USBButton->Checked == true)
			{
				UnMounted->Checked = false;
				Mounted->Checked = true;
			}
		}
	}
	private: System::Void NameTitleBox_TextChanged_1(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void CompanyModelTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		ap.getname();
		ap.getmodel_no();
	}
	private: System::Void PlayButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (ONButton->Checked == true)
		{
			PauseButton->Visible = true;
			PlayButton->Visible = false;
			IsPlaying->Checked = true;
			if (USBButton->Checked == true)
			{
				string s = ap.PlayMusicUSB();
				String^ str2 = gcnew String(s.c_str());
				PlayingSongBox->Text = str2;
			}
			else if (CDButton->Checked == true)
			{
				string s = ap.PlayMusicCD();
				String^ str2 = gcnew String(s.c_str());
				PlayingSongBox->Text = str2;
			}
		}
	}
	private: System::Void MountButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (ONButton->Checked == true)
		{
			PlayButton->Enabled = true;
			PauseButton->Enabled = true;
			NextButton->Enabled = true;
			PreviousButton->Enabled = true;
			ShuffleButton->Enabled = true;
			CD obj1;
			if (USBButton->Checked == false && CDButton->Checked == false)
			{
				CDButton->Checked = true;
				if (Mounted->Checked == true)
				{
					obj1.openCD();
					obj1.SavePlayListCD();
					for (int i = 0; i < CDSize; i++)
					{
						string str = obj1.PlayListCD();
						String^ str3 = gcnew String(str.c_str());
						PlayList->Items->Add(str3);
					}
					IsPlaying->Checked = true;
					string s = ap.PlayMusicCD();
					String^ str2 = gcnew String(s.c_str());
					PlayingSongBox->Text = str2;
					PlayList->SetSelected(ap.GetIndexCD(s), true);
				}
			}
			else if (USBButton->Checked == true && CDButton->Checked == false)
			{
				USBButton->Checked = false;
				CDButton->Checked = true;
				if (Mounted->Checked == true)
				{
					ap.CloseMusicUSB();
					PlayList->Items->Clear();
					obj1.openCD();
					obj1.SavePlayListCD();
					for (int i = 0; i < CDSize; i++)
					{
						string str = obj1.PlayListCD();
						String^ str3 = gcnew String(str.c_str());
						PlayList->Items->Add(str3);
					}
					IsPlaying->Checked = true;
					string s = ap.PlayMusicCD();
					String^ str2 = gcnew String(s.c_str());
					PlayingSongBox->Text = str2;
					PlayList->SetSelected(ap.GetIndexCD(s), true);
				}
			}
			else if (USBButton->Checked == false && CDButton->Checked == true)
			{
				USBButton->Checked = true;
				CDButton->Checked = false;
				if (Mounted->Checked == true)
				{
					ap.CloseMusicCD();
					PlayList->Items->Clear();
					USB obj2;
					obj2.opencloseUSB();
					obj2.SavePlayListUSB();
					for (int i = 0; i < USBSize; i++)
					{
						string str = obj2.PlayListUSB();
						String^ str3 = gcnew String(str.c_str());
						PlayList->Items->Add(str3);
					}
					IsPlaying->Checked = true;
					string s = ap.PlayMusicUSB();
					String^ str2 = gcnew String(s.c_str());
					PlayingSongBox->Text = str2;
					PlayList->SetSelected(ap.GetIndexUSB(s), true);
				}
			}
		}
	}
	private: System::Void PauseButton_Click(System::Object^ sender, System::EventArgs^ e) {
		PlayButton->Visible = true;
		PauseButton->Visible = false;
		if (USBButton->Checked == true)
		{
			IsPlaying->Checked = false;
			string s = ap.PauseMusicUSB();
			String^ str2 = gcnew String(s.c_str());
			PlayingSongBox->Text = str2;
		}
		else if (CDButton->Checked == true)
		{
			IsPlaying->Checked = false;
			string s = ap.PauseMusicCD();
			String^ str2 = gcnew String(s.c_str());
			PlayingSongBox->Text = str2;
		}
	}
	private: System::Void IsPlaying_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (IsPlaying->Checked == true)
		{
			PauseButton->Visible = true;
			PlayButton->Visible = false;
		}
		else if (IsPlaying->Checked == false)
		{
			PlayButton->Visible = true;
			PauseButton->Visible = false;
		}
	}
	private: System::Void NextButton_Click(System::Object^ sender, System::EventArgs^ e) {
		PauseButton->Visible = true;
		PlayButton->Visible = false;
		if (USBButton->Checked == true)
		{
			string s = ap.NextMusicUSB();
			String^ str2 = gcnew String(s.c_str());
			PlayingSongBox->Text = str2;
			PlayList->SetSelected(ap.GetIndexUSB(s), true);
		}
		else if (CDButton->Checked == true)
		{
			string s = ap.NextMusicCD();
			String^ str2 = gcnew String(s.c_str());
			PlayingSongBox->Text = str2;
			PlayList->SetSelected(ap.GetIndexCD(s), true);
		}
	}
	private: System::Void PlayingSongBox_TextChanged_2(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void progressBar1_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void SearchLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ShuffleButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (ONButton->Checked == true)
		{
			if (CDButton->Checked == true)
			{
				string s = ap.ShuffleCD();
				String^ str2 = gcnew String(s.c_str());
				PlayingSongBox->Text = str2;
				PlayList->SetSelected(ap.GetIndexCD(s), true);
			}
			else if (USBButton->Checked == true)
			{
				string s = ap.ShuffleUSB();
				String^ str2 = gcnew String(s.c_str());
				PlayingSongBox->Text = str2;
				PlayList->SetSelected(ap.GetIndexUSB(s), true);
			}
			PauseButton->Visible = true;
			PlayButton->Visible = false;
		}
	}
	private: System::Void SearchButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int result = PlayList->FindStringExact(SearchTextBox->Text);
		if (result >= 0)
		{
			PlayList->SetSelected(result, true);
			for (int i = 0; i < (PlayList->Items->Count); )
			{
				bool res = PlayList->GetSelected(i);
				if (!res)
				{
					PlayList->Items->RemoveAt(i);
				}
				else
				{
					i++;
				}
			}
		}
		else
		{
			SearchTextBox->Text = "Song Not Found!!";
		}
	}
	private: System::Void c(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}


********PLAYLIST_TEXTFILE_DATA********

***** CD PlayList*****
8) Aay.mp3
8) CDaud.mp3
8) CDbirds10.mp3
8) CDbirds6.mp3
8) CDbirds7.mp3
8) CDbirds8.mp3
8) CDbirds9.mp3


***** USB PlayList*****
10) Arif_Lohar_Jis_Tan_Nu_Lagdi_Aye_Barcelona_Trip_2014(128k).mp3
10) Baari_by_Bilal_Saeed_and_Momina_Mustehsan___Official_Music_Video___Latest_Song_2019(128k).mp3
10) Changeyan_Naal_La_Lo_Yaarian - _Syed_FasiUddin_Soharwardi.mp3
10) Coke_Studio_Season_12__Wohi_Khuda_Hai__Atif_Aslam(128k).mp3
10) Coke_Studio_Season_8_Tajdar - e - Haram_Atif_Aslam(128k).mp3
10) Ishq_Bulleh_Nu_Nachave(128k).mp3
10) Mujhe_Insaniyat_Ki_Khidmat_Karni_Hai_New_Song_2019(128k).mp3
10) Tere_Rang_Rang_(Abrar - Ul - Haq).mp3(128k).mp3
10) USBAlif_Allah.mp3

