#pragma once
#include <vector>
#include <string>
#include <typeinfo>
namespace ChessGame {
	using namespace System;
	using namespace std;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Threading::Tasks;
	using namespace System::Windows::Forms;
	using namespace System::Xml::Serialization;
	public ref class ChessBoardEditor : public System::Windows::Forms::Form
	{
	public: String^ nowFigure = "";
		  ChessBoardEditor(void)
		  {
			  InitializeComponent();
		  }
		  List<Figure^>^ figures = gcnew List<Figure^>();
	public: System::Void figureClick(System::Object^ sender, System::EventArgs^ e)
	{
		nowFigure = ((Button^)sender)->Name;
		((Button^)sender)->BackColor = System::Drawing::Color::Black;
	}
	public: System::Void anyField_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (nowFigure->Length != 0)
		{
			auto pictureBox = (PictureBox^)sender;
			if (nowFigure == L"whiteKing")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\whiteKing.png");
			else if (nowFigure == L"blackKing")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\blackKing.png");
			else if (nowFigure == L"whiteQueen")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\whiteQueen.png");
			else if (nowFigure == L"blackQueen")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\blackQueen.png");
			else if (nowFigure == L"whiteRoof")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\whiteRoof.png");
			else if (nowFigure == L"blackRoof")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\blackRoof.png");
			else if (nowFigure == L"whiteBishop")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\whiteBishop.png");
			else if (nowFigure == L"blackBishop")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\blackBishop.png");
			else if (nowFigure == L"whiteKnight")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\whiteKnight.png");
			else if (nowFigure == L"blackKnight")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\blackKnight.png");
			else if (nowFigure == L"whitePawn")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\whitePawn.png");
			else if (nowFigure == L"blackPawn")
				pictureBox->BackgroundImage = Image::FromFile("C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\blackPawn.png");

			Figure^ newFigure = gcnew Figure();
			newFigure->color = nowFigure->Substring(0, 5);
			newFigure->name = nowFigure->Substring(5, nowFigure->Length - 5);
			newFigure->location = pictureBox->Name;
			figures->Add(newFigure);
		}
	}
	private: List<PictureBox^>^ pictureBoxes = gcnew List<PictureBox^>();
		   // XmlSerializer^ formatter = gcnew XmlSerializer(typeid(std::vector<Figure>), std::vector<std::type_info> {typeid(Figure)});

	private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		for each (Control ^ x in this->Controls)
		{
			if (dynamic_cast<PictureBox^>(x) != nullptr)
			{
				(static_cast<PictureBox^>(x))->BackgroundImage = nullptr;
			}
		}
	}
	private: System::Void îòêðûòüToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
			return;
		// ïîëó÷àåì âûáðàííûé ôàéë
		String^ filename = openFileDialog1->FileName;
		// ÷èòàåì ôàéë â ñòðîêó

		// ñîõðàíèëè â ñïèñîê
		//figures = (List<Figure^>)formatter::Deserialize(openFileDialog1->OpenFile());
		for each (Control ^ x in this->Controls)
		{
			if (dynamic_cast<PictureBox^>(x) != nullptr)
			{
				(static_cast<PictureBox^>(x))->BackgroundImage = nullptr;
			}
		}
		for each (Figure ^ figure in figures)
		{
			for each (Control ^ x in Controls)
			{
				if (dynamic_cast<PictureBox^>(x) != nullptr)
				{
					if (figure->location == x->Name)
					{
						auto filepath = L"C:\\Users\\USER\\source\\repos\\\ChessGame\\\ChessGame\\images\\" + figure->color + figure->name + L".png";
						(static_cast<PictureBox^>(x))->BackgroundImage = Image::FromFile(filepath);
					}
				}
			}
		}
	}
	private: System::Void ñîõðàíèòüToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Stream^ myStream;
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
		saveFileDialog1->Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
		saveFileDialog1->FilterIndex = 2;
		saveFileDialog1->RestoreDirectory = false;
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if ((myStream = saveFileDialog1->OpenFile()) != nullptr)
			{

				//formatter->Serialize(myStream, figures);


				myStream->Close();
			}
		}
	}
	protected:
		~ChessBoardEditor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ clearButton;
	protected:
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ h1;
	private: System::Windows::Forms::PictureBox^ g1;
	private: System::Windows::Forms::PictureBox^ f1;
	private: System::Windows::Forms::PictureBox^ e1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::PictureBox^ d1;
	private: System::Windows::Forms::PictureBox^ c1;
	private: System::Windows::Forms::PictureBox^ b1;
	private: System::Windows::Forms::PictureBox^ a1;
	private: System::Windows::Forms::PictureBox^ h2;
	private: System::Windows::Forms::PictureBox^ g2;
	private: System::Windows::Forms::PictureBox^ f2;
	private: System::Windows::Forms::PictureBox^ e2;
	private: System::Windows::Forms::PictureBox^ d2;
	private: System::Windows::Forms::PictureBox^ c2;
	private: System::Windows::Forms::PictureBox^ b2;
	private: System::Windows::Forms::PictureBox^ a2;
	private: System::Windows::Forms::PictureBox^ h3;
	private: System::Windows::Forms::ToolStripMenuItem^ ôàéëToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ îòêðûòüToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ñîõðàíèòüToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ g3;
	private: System::Windows::Forms::PictureBox^ f3;
	private: System::Windows::Forms::PictureBox^ e3;
	private: System::Windows::Forms::PictureBox^ d3;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::PictureBox^ c3;
	private: System::Windows::Forms::PictureBox^ b3;
	private: System::Windows::Forms::PictureBox^ a3;
	private: System::Windows::Forms::PictureBox^ h4;
	private: System::Windows::Forms::PictureBox^ g4;
	private: System::Windows::Forms::PictureBox^ f4;
	private: System::Windows::Forms::PictureBox^ e4;
	private: System::Windows::Forms::PictureBox^ d4;
	private: System::Windows::Forms::PictureBox^ c4;
	private: System::Windows::Forms::PictureBox^ b4;
	private: System::Windows::Forms::PictureBox^ a4;
	private: System::Windows::Forms::PictureBox^ h5;
	private: System::Windows::Forms::PictureBox^ g5;
	private: System::Windows::Forms::PictureBox^ f5;
	private: System::Windows::Forms::PictureBox^ e5;
	private: System::Windows::Forms::PictureBox^ d5;
	private: System::Windows::Forms::PictureBox^ c5;
	private: System::Windows::Forms::PictureBox^ b5;
	private: System::Windows::Forms::PictureBox^ a5;
	private: System::Windows::Forms::PictureBox^ h6;
	private: System::Windows::Forms::PictureBox^ g6;
	private: System::Windows::Forms::PictureBox^ f6;
	private: System::Windows::Forms::PictureBox^ e6;
	private: System::Windows::Forms::PictureBox^ d6;
	private: System::Windows::Forms::PictureBox^ c6;
	private: System::Windows::Forms::PictureBox^ b6;
	private: System::Windows::Forms::PictureBox^ a6;
	private: System::Windows::Forms::PictureBox^ h7;
	private: System::Windows::Forms::PictureBox^ g7;
	private: System::Windows::Forms::PictureBox^ f7;
	private: System::Windows::Forms::PictureBox^ e7;
	private: System::Windows::Forms::PictureBox^ d7;
	private: System::Windows::Forms::PictureBox^ c7;
	private: System::Windows::Forms::PictureBox^ b7;
	private: System::Windows::Forms::PictureBox^ a7;
	private: System::Windows::Forms::PictureBox^ h8;
	private: System::Windows::Forms::PictureBox^ g8;
	private: System::Windows::Forms::PictureBox^ f8;
	private: System::Windows::Forms::PictureBox^ e8;
	private: System::Windows::Forms::PictureBox^ d8;
	private: System::Windows::Forms::PictureBox^ c8;
	private: System::Windows::Forms::PictureBox^ b8;
	private: System::Windows::Forms::PictureBox^ a8;
	private: System::Windows::Forms::Button^ blackPawn;
	private: System::Windows::Forms::Button^ blackKnight;
	private: System::Windows::Forms::Button^ blackBishop;
	private: System::Windows::Forms::Button^ blackRoof;
	private: System::Windows::Forms::Button^ blackQueen;
	private: System::Windows::Forms::Button^ blackKing;
	private: System::Windows::Forms::Button^ whitePawn;
	private: System::Windows::Forms::Button^ whiteKnight;
	private: System::Windows::Forms::Button^ whiteBishop;
	private: System::Windows::Forms::Button^ whiteRoof;
	private: System::Windows::Forms::Button^ whiteQueen;
	private: System::Windows::Forms::Button^ whiteKing;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåðåìåííàÿ êîíñòðóêòîðà.
		/// </summary>
		System::ComponentModel::Container^ components;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òðåáóåìûé ìåòîä äëÿ ïîääåðæêè êîíñòðóêòîðà — íå èçìåíÿéòå 
		/// ñîäåðæèìîå ýòîãî ìåòîäà ñ ïîìîùüþ ðåäàêòîðà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ChessBoardEditor::typeid));
			this->clearButton = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->h1 = (gcnew System::Windows::Forms::PictureBox());
			this->g1 = (gcnew System::Windows::Forms::PictureBox());
			this->f1 = (gcnew System::Windows::Forms::PictureBox());
			this->e1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->d1 = (gcnew System::Windows::Forms::PictureBox());
			this->c1 = (gcnew System::Windows::Forms::PictureBox());
			this->b1 = (gcnew System::Windows::Forms::PictureBox());
			this->a1 = (gcnew System::Windows::Forms::PictureBox());
			this->h2 = (gcnew System::Windows::Forms::PictureBox());
			this->g2 = (gcnew System::Windows::Forms::PictureBox());
			this->f2 = (gcnew System::Windows::Forms::PictureBox());
			this->e2 = (gcnew System::Windows::Forms::PictureBox());
			this->d2 = (gcnew System::Windows::Forms::PictureBox());
			this->c2 = (gcnew System::Windows::Forms::PictureBox());
			this->b2 = (gcnew System::Windows::Forms::PictureBox());
			this->a2 = (gcnew System::Windows::Forms::PictureBox());
			this->h3 = (gcnew System::Windows::Forms::PictureBox());
			this->ôàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îòêðûòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõðàíèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->g3 = (gcnew System::Windows::Forms::PictureBox());
			this->f3 = (gcnew System::Windows::Forms::PictureBox());
			this->e3 = (gcnew System::Windows::Forms::PictureBox());
			this->d3 = (gcnew System::Windows::Forms::PictureBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->c3 = (gcnew System::Windows::Forms::PictureBox());
			this->b3 = (gcnew System::Windows::Forms::PictureBox());
			this->a3 = (gcnew System::Windows::Forms::PictureBox());
			this->h4 = (gcnew System::Windows::Forms::PictureBox());
			this->g4 = (gcnew System::Windows::Forms::PictureBox());
			this->f4 = (gcnew System::Windows::Forms::PictureBox());
			this->e4 = (gcnew System::Windows::Forms::PictureBox());
			this->d4 = (gcnew System::Windows::Forms::PictureBox());
			this->c4 = (gcnew System::Windows::Forms::PictureBox());
			this->b4 = (gcnew System::Windows::Forms::PictureBox());
			this->a4 = (gcnew System::Windows::Forms::PictureBox());
			this->h5 = (gcnew System::Windows::Forms::PictureBox());
			this->g5 = (gcnew System::Windows::Forms::PictureBox());
			this->f5 = (gcnew System::Windows::Forms::PictureBox());
			this->e5 = (gcnew System::Windows::Forms::PictureBox());
			this->d5 = (gcnew System::Windows::Forms::PictureBox());
			this->c5 = (gcnew System::Windows::Forms::PictureBox());
			this->b5 = (gcnew System::Windows::Forms::PictureBox());
			this->a5 = (gcnew System::Windows::Forms::PictureBox());
			this->h6 = (gcnew System::Windows::Forms::PictureBox());
			this->g6 = (gcnew System::Windows::Forms::PictureBox());
			this->f6 = (gcnew System::Windows::Forms::PictureBox());
			this->e6 = (gcnew System::Windows::Forms::PictureBox());
			this->d6 = (gcnew System::Windows::Forms::PictureBox());
			this->c6 = (gcnew System::Windows::Forms::PictureBox());
			this->b6 = (gcnew System::Windows::Forms::PictureBox());
			this->a6 = (gcnew System::Windows::Forms::PictureBox());
			this->h7 = (gcnew System::Windows::Forms::PictureBox());
			this->g7 = (gcnew System::Windows::Forms::PictureBox());
			this->f7 = (gcnew System::Windows::Forms::PictureBox());
			this->e7 = (gcnew System::Windows::Forms::PictureBox());
			this->d7 = (gcnew System::Windows::Forms::PictureBox());
			this->c7 = (gcnew System::Windows::Forms::PictureBox());
			this->b7 = (gcnew System::Windows::Forms::PictureBox());
			this->a7 = (gcnew System::Windows::Forms::PictureBox());
			this->h8 = (gcnew System::Windows::Forms::PictureBox());
			this->g8 = (gcnew System::Windows::Forms::PictureBox());
			this->f8 = (gcnew System::Windows::Forms::PictureBox());
			this->e8 = (gcnew System::Windows::Forms::PictureBox());
			this->d8 = (gcnew System::Windows::Forms::PictureBox());
			this->c8 = (gcnew System::Windows::Forms::PictureBox());
			this->b8 = (gcnew System::Windows::Forms::PictureBox());
			this->a8 = (gcnew System::Windows::Forms::PictureBox());
			this->blackPawn = (gcnew System::Windows::Forms::Button());
			this->blackKnight = (gcnew System::Windows::Forms::Button());
			this->blackBishop = (gcnew System::Windows::Forms::Button());
			this->blackRoof = (gcnew System::Windows::Forms::Button());
			this->blackQueen = (gcnew System::Windows::Forms::Button());
			this->blackKing = (gcnew System::Windows::Forms::Button());
			this->whitePawn = (gcnew System::Windows::Forms::Button());
			this->whiteKnight = (gcnew System::Windows::Forms::Button());
			this->whiteBishop = (gcnew System::Windows::Forms::Button());
			this->whiteRoof = (gcnew System::Windows::Forms::Button());
			this->whiteQueen = (gcnew System::Windows::Forms::Button());
			this->whiteKing = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a8))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// clearButton
			// 
			this->clearButton->FlatAppearance->BorderColor = System::Drawing::Color::WhiteSmoke;
			this->clearButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->clearButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->clearButton->Location = System::Drawing::Point(12, 70);
			this->clearButton->Name = L"clearButton";
			this->clearButton->Size = System::Drawing::Size(133, 64);
			this->clearButton->TabIndex = 201;
			this->clearButton->Text = L"Î÷èñòèòü äîñêó";
			this->clearButton->UseVisualStyleBackColor = true;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(189, 118);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(16, 16);
			this->label16->TabIndex = 200;
			this->label16->Text = L"8";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(189, 183);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(16, 16);
			this->label15->TabIndex = 199;
			this->label15->Text = L"7";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(189, 246);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(16, 16);
			this->label14->TabIndex = 198;
			this->label14->Text = L"6";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(189, 309);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(16, 16);
			this->label13->TabIndex = 197;
			this->label13->Text = L"5";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(189, 373);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(16, 16);
			this->label12->TabIndex = 196;
			this->label12->Text = L"4";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(189, 435);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(16, 16);
			this->label11->TabIndex = 195;
			this->label11->Text = L"3";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(189, 502);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(16, 16);
			this->label10->TabIndex = 194;
			this->label10->Text = L"2";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(189, 561);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(16, 16);
			this->label9->TabIndex = 193;
			this->label9->Text = L"1";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(682, 605);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(19, 16);
			this->label8->TabIndex = 192;
			this->label8->Text = L"H";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(617, 605);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(19, 16);
			this->label7->TabIndex = 191;
			this->label7->Text = L"G";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(554, 605);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(17, 16);
			this->label6->TabIndex = 190;
			this->label6->Text = L"F";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(489, 606);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(18, 16);
			this->label5->TabIndex = 189;
			this->label5->Text = L"E";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(426, 606);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(19, 16);
			this->label4->TabIndex = 188;
			this->label4->Text = L"D";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(362, 606);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(18, 16);
			this->label3->TabIndex = 187;
			this->label3->Text = L"C";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(297, 606);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(18, 16);
			this->label2->TabIndex = 186;
			this->label2->Text = L"B";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(235, 606);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(18, 16);
			this->label1->TabIndex = 185;
			this->label1->Text = L"A";
			// 
			// h1
			// 
			this->h1->BackColor = System::Drawing::Color::White;
			this->h1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->h1->Location = System::Drawing::Point(657, 539);
			this->h1->Name = L"h1";
			this->h1->Size = System::Drawing::Size(64, 64);
			this->h1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->h1->TabIndex = 184;
			this->h1->TabStop = false;
			// 
			// g1
			// 
			this->g1->BackColor = System::Drawing::Color::Black;
			this->g1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g1->Location = System::Drawing::Point(593, 539);
			this->g1->Name = L"g1";
			this->g1->Size = System::Drawing::Size(64, 64);
			this->g1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->g1->TabIndex = 183;
			this->g1->TabStop = false;
			// 
			// f1
			// 
			this->f1->BackColor = System::Drawing::Color::White;
			this->f1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f1->Location = System::Drawing::Point(529, 539);
			this->f1->Name = L"f1";
			this->f1->Size = System::Drawing::Size(64, 64);
			this->f1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->f1->TabIndex = 182;
			this->f1->TabStop = false;
			// 
			// e1
			// 
			this->e1->BackColor = System::Drawing::Color::Black;
			this->e1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e1->Location = System::Drawing::Point(465, 539);
			this->e1->Name = L"e1";
			this->e1->Size = System::Drawing::Size(64, 64);
			this->e1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->e1->TabIndex = 181;
			this->e1->TabStop = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// d1
			// 
			this->d1->BackColor = System::Drawing::Color::White;
			this->d1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d1->Location = System::Drawing::Point(401, 539);
			this->d1->Name = L"d1";
			this->d1->Size = System::Drawing::Size(64, 64);
			this->d1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->d1->TabIndex = 180;
			this->d1->TabStop = false;
			// 
			// c1
			// 
			this->c1->BackColor = System::Drawing::Color::Black;
			this->c1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c1->Location = System::Drawing::Point(337, 539);
			this->c1->Name = L"c1";
			this->c1->Size = System::Drawing::Size(64, 64);
			this->c1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->c1->TabIndex = 179;
			this->c1->TabStop = false;
			// 
			// b1
			// 
			this->b1->BackColor = System::Drawing::Color::White;
			this->b1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b1->Location = System::Drawing::Point(273, 539);
			this->b1->Name = L"b1";
			this->b1->Size = System::Drawing::Size(64, 64);
			this->b1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->b1->TabIndex = 178;
			this->b1->TabStop = false;
			// 
			// a1
			// 
			this->a1->BackColor = System::Drawing::Color::Black;
			this->a1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a1->Location = System::Drawing::Point(209, 539);
			this->a1->Name = L"a1";
			this->a1->Size = System::Drawing::Size(64, 64);
			this->a1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->a1->TabIndex = 177;
			this->a1->TabStop = false;
			// 
			// h2
			// 
			this->h2->BackColor = System::Drawing::Color::Black;
			this->h2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->h2->Location = System::Drawing::Point(657, 475);
			this->h2->Name = L"h2";
			this->h2->Size = System::Drawing::Size(64, 64);
			this->h2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->h2->TabIndex = 176;
			this->h2->TabStop = false;
			// 
			// g2
			// 
			this->g2->BackColor = System::Drawing::Color::White;
			this->g2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g2->Location = System::Drawing::Point(593, 475);
			this->g2->Name = L"g2";
			this->g2->Size = System::Drawing::Size(64, 64);
			this->g2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->g2->TabIndex = 175;
			this->g2->TabStop = false;
			// 
			// f2
			// 
			this->f2->BackColor = System::Drawing::Color::Black;
			this->f2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f2->Location = System::Drawing::Point(529, 475);
			this->f2->Name = L"f2";
			this->f2->Size = System::Drawing::Size(64, 64);
			this->f2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->f2->TabIndex = 174;
			this->f2->TabStop = false;
			// 
			// e2
			// 
			this->e2->BackColor = System::Drawing::Color::White;
			this->e2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e2->Location = System::Drawing::Point(465, 475);
			this->e2->Name = L"e2";
			this->e2->Size = System::Drawing::Size(64, 64);
			this->e2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->e2->TabIndex = 173;
			this->e2->TabStop = false;
			// 
			// d2
			// 
			this->d2->BackColor = System::Drawing::Color::Black;
			this->d2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d2->Location = System::Drawing::Point(401, 475);
			this->d2->Name = L"d2";
			this->d2->Size = System::Drawing::Size(64, 64);
			this->d2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->d2->TabIndex = 172;
			this->d2->TabStop = false;
			// 
			// c2
			// 
			this->c2->BackColor = System::Drawing::Color::White;
			this->c2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c2->Location = System::Drawing::Point(337, 475);
			this->c2->Name = L"c2";
			this->c2->Size = System::Drawing::Size(64, 64);
			this->c2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->c2->TabIndex = 171;
			this->c2->TabStop = false;
			// 
			// b2
			// 
			this->b2->BackColor = System::Drawing::Color::Black;
			this->b2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b2->Location = System::Drawing::Point(273, 475);
			this->b2->Name = L"b2";
			this->b2->Size = System::Drawing::Size(64, 64);
			this->b2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->b2->TabIndex = 170;
			this->b2->TabStop = false;
			// 
			// a2
			// 
			this->a2->BackColor = System::Drawing::Color::White;
			this->a2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a2->Location = System::Drawing::Point(209, 475);
			this->a2->Name = L"a2";
			this->a2->Size = System::Drawing::Size(64, 64);
			this->a2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->a2->TabIndex = 169;
			this->a2->TabStop = false;
			// 
			// h3
			// 
			this->h3->BackColor = System::Drawing::Color::White;
			this->h3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->h3->Location = System::Drawing::Point(657, 411);
			this->h3->Name = L"h3";
			this->h3->Size = System::Drawing::Size(64, 64);
			this->h3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->h3->TabIndex = 168;
			this->h3->TabStop = false;
			// 
			// ôàéëToolStripMenuItem
			// 
			this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->îòêðûòüToolStripMenuItem,
					this->ñîõðàíèòüToolStripMenuItem
			});
			this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
			this->ôàéëToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->ôàéëToolStripMenuItem->Text = L"Ôàéë";
			// 
			// îòêðûòüToolStripMenuItem
			// 
			this->îòêðûòüToolStripMenuItem->Name = L"îòêðûòüToolStripMenuItem";
			this->îòêðûòüToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->îòêðûòüToolStripMenuItem->Text = L"Îòêðûòü";
			// 
			// ñîõðàíèòüToolStripMenuItem
			// 
			this->ñîõðàíèòüToolStripMenuItem->Name = L"ñîõðàíèòüToolStripMenuItem";
			this->ñîõðàíèòüToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->ñîõðàíèòüToolStripMenuItem->Text = L"Ñîõðàíèòü";
			// 
			// g3
			// 
			this->g3->BackColor = System::Drawing::Color::Black;
			this->g3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g3->Location = System::Drawing::Point(593, 411);
			this->g3->Name = L"g3";
			this->g3->Size = System::Drawing::Size(64, 64);
			this->g3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->g3->TabIndex = 167;
			this->g3->TabStop = false;
			// 
			// f3
			// 
			this->f3->BackColor = System::Drawing::Color::White;
			this->f3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f3->Location = System::Drawing::Point(529, 411);
			this->f3->Name = L"f3";
			this->f3->Size = System::Drawing::Size(64, 64);
			this->f3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->f3->TabIndex = 166;
			this->f3->TabStop = false;
			// 
			// e3
			// 
			this->e3->BackColor = System::Drawing::Color::Black;
			this->e3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e3->Location = System::Drawing::Point(465, 411);
			this->e3->Name = L"e3";
			this->e3->Size = System::Drawing::Size(64, 64);
			this->e3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->e3->TabIndex = 165;
			this->e3->TabStop = false;
			// 
			// d3
			// 
			this->d3->BackColor = System::Drawing::Color::White;
			this->d3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d3->Location = System::Drawing::Point(401, 411);
			this->d3->Name = L"d3";
			this->d3->Size = System::Drawing::Size(64, 64);
			this->d3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->d3->TabIndex = 164;
			this->d3->TabStop = false;
			// 
			// c3
			// 
			this->c3->BackColor = System::Drawing::Color::Black;
			this->c3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c3->Location = System::Drawing::Point(337, 411);
			this->c3->Name = L"c3";
			this->c3->Size = System::Drawing::Size(64, 64);
			this->c3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->c3->TabIndex = 163;
			this->c3->TabStop = false;
			// 
			// b3
			// 
			this->b3->BackColor = System::Drawing::Color::White;
			this->b3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b3->Location = System::Drawing::Point(273, 411);
			this->b3->Name = L"b3";
			this->b3->Size = System::Drawing::Size(64, 64);
			this->b3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->b3->TabIndex = 162;
			this->b3->TabStop = false;
			// 
			// a3
			// 
			this->a3->BackColor = System::Drawing::Color::Black;
			this->a3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a3->Location = System::Drawing::Point(209, 411);
			this->a3->Name = L"a3";
			this->a3->Size = System::Drawing::Size(64, 64);
			this->a3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->a3->TabIndex = 161;
			this->a3->TabStop = false;
			// 
			// h4
			// 
			this->h4->BackColor = System::Drawing::Color::Black;
			this->h4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->h4->Location = System::Drawing::Point(657, 347);
			this->h4->Name = L"h4";
			this->h4->Size = System::Drawing::Size(64, 64);
			this->h4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->h4->TabIndex = 160;
			this->h4->TabStop = false;
			// 
			// g4
			// 
			this->g4->BackColor = System::Drawing::Color::White;
			this->g4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g4->Location = System::Drawing::Point(593, 347);
			this->g4->Name = L"g4";
			this->g4->Size = System::Drawing::Size(64, 64);
			this->g4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->g4->TabIndex = 159;
			this->g4->TabStop = false;
			// 
			// f4
			// 
			this->f4->BackColor = System::Drawing::Color::Black;
			this->f4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f4->Location = System::Drawing::Point(529, 347);
			this->f4->Name = L"f4";
			this->f4->Size = System::Drawing::Size(64, 64);
			this->f4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->f4->TabIndex = 158;
			this->f4->TabStop = false;
			// 
			// e4
			// 
			this->e4->BackColor = System::Drawing::Color::White;
			this->e4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e4->Location = System::Drawing::Point(465, 347);
			this->e4->Name = L"e4";
			this->e4->Size = System::Drawing::Size(64, 64);
			this->e4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->e4->TabIndex = 157;
			this->e4->TabStop = false;
			// 
			// d4
			// 
			this->d4->BackColor = System::Drawing::Color::Black;
			this->d4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d4->Location = System::Drawing::Point(401, 347);
			this->d4->Name = L"d4";
			this->d4->Size = System::Drawing::Size(64, 64);
			this->d4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->d4->TabIndex = 156;
			this->d4->TabStop = false;
			// 
			// c4
			// 
			this->c4->BackColor = System::Drawing::Color::White;
			this->c4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c4->Location = System::Drawing::Point(337, 347);
			this->c4->Name = L"c4";
			this->c4->Size = System::Drawing::Size(64, 64);
			this->c4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->c4->TabIndex = 155;
			this->c4->TabStop = false;
			// 
			// b4
			// 
			this->b4->BackColor = System::Drawing::Color::Black;
			this->b4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b4->Location = System::Drawing::Point(273, 347);
			this->b4->Name = L"b4";
			this->b4->Size = System::Drawing::Size(64, 64);
			this->b4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->b4->TabIndex = 154;
			this->b4->TabStop = false;
			// 
			// a4
			// 
			this->a4->BackColor = System::Drawing::Color::White;
			this->a4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a4->Location = System::Drawing::Point(209, 347);
			this->a4->Name = L"a4";
			this->a4->Size = System::Drawing::Size(64, 64);
			this->a4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->a4->TabIndex = 153;
			this->a4->TabStop = false;
			// 
			// h5
			// 
			this->h5->BackColor = System::Drawing::Color::White;
			this->h5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->h5->Location = System::Drawing::Point(657, 283);
			this->h5->Name = L"h5";
			this->h5->Size = System::Drawing::Size(64, 64);
			this->h5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->h5->TabIndex = 152;
			this->h5->TabStop = false;
			// 
			// g5
			// 
			this->g5->BackColor = System::Drawing::Color::Black;
			this->g5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g5->Location = System::Drawing::Point(593, 283);
			this->g5->Name = L"g5";
			this->g5->Size = System::Drawing::Size(64, 64);
			this->g5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->g5->TabIndex = 151;
			this->g5->TabStop = false;
			// 
			// f5
			// 
			this->f5->BackColor = System::Drawing::Color::White;
			this->f5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f5->Location = System::Drawing::Point(529, 283);
			this->f5->Name = L"f5";
			this->f5->Size = System::Drawing::Size(64, 64);
			this->f5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->f5->TabIndex = 150;
			this->f5->TabStop = false;
			// 
			// e5
			// 
			this->e5->BackColor = System::Drawing::Color::Black;
			this->e5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e5->Location = System::Drawing::Point(465, 283);
			this->e5->Name = L"e5";
			this->e5->Size = System::Drawing::Size(64, 64);
			this->e5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->e5->TabIndex = 149;
			this->e5->TabStop = false;
			// 
			// d5
			// 
			this->d5->BackColor = System::Drawing::Color::White;
			this->d5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d5->Location = System::Drawing::Point(401, 283);
			this->d5->Name = L"d5";
			this->d5->Size = System::Drawing::Size(64, 64);
			this->d5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->d5->TabIndex = 148;
			this->d5->TabStop = false;
			// 
			// c5
			// 
			this->c5->BackColor = System::Drawing::Color::Black;
			this->c5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c5->Location = System::Drawing::Point(337, 283);
			this->c5->Name = L"c5";
			this->c5->Size = System::Drawing::Size(64, 64);
			this->c5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->c5->TabIndex = 147;
			this->c5->TabStop = false;
			// 
			// b5
			// 
			this->b5->BackColor = System::Drawing::Color::White;
			this->b5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b5->Location = System::Drawing::Point(273, 283);
			this->b5->Name = L"b5";
			this->b5->Size = System::Drawing::Size(64, 64);
			this->b5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->b5->TabIndex = 146;
			this->b5->TabStop = false;
			// 
			// a5
			// 
			this->a5->BackColor = System::Drawing::Color::Black;
			this->a5->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a5->Location = System::Drawing::Point(209, 283);
			this->a5->Name = L"a5";
			this->a5->Size = System::Drawing::Size(64, 64);
			this->a5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->a5->TabIndex = 145;
			this->a5->TabStop = false;
			// 
			// h6
			// 
			this->h6->BackColor = System::Drawing::Color::Black;
			this->h6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->h6->Location = System::Drawing::Point(657, 219);
			this->h6->Name = L"h6";
			this->h6->Size = System::Drawing::Size(64, 64);
			this->h6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->h6->TabIndex = 144;
			this->h6->TabStop = false;
			// 
			// g6
			// 
			this->g6->BackColor = System::Drawing::Color::White;
			this->g6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g6->Location = System::Drawing::Point(593, 219);
			this->g6->Name = L"g6";
			this->g6->Size = System::Drawing::Size(64, 64);
			this->g6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->g6->TabIndex = 143;
			this->g6->TabStop = false;
			// 
			// f6
			// 
			this->f6->BackColor = System::Drawing::Color::Black;
			this->f6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f6->Location = System::Drawing::Point(529, 219);
			this->f6->Name = L"f6";
			this->f6->Size = System::Drawing::Size(64, 64);
			this->f6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->f6->TabIndex = 142;
			this->f6->TabStop = false;
			// 
			// e6
			// 
			this->e6->BackColor = System::Drawing::Color::White;
			this->e6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e6->Location = System::Drawing::Point(465, 219);
			this->e6->Name = L"e6";
			this->e6->Size = System::Drawing::Size(64, 64);
			this->e6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->e6->TabIndex = 141;
			this->e6->TabStop = false;
			// 
			// d6
			// 
			this->d6->BackColor = System::Drawing::Color::Black;
			this->d6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d6->Location = System::Drawing::Point(401, 219);
			this->d6->Name = L"d6";
			this->d6->Size = System::Drawing::Size(64, 64);
			this->d6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->d6->TabIndex = 140;
			this->d6->TabStop = false;
			// 
			// c6
			// 
			this->c6->BackColor = System::Drawing::Color::White;
			this->c6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c6->Location = System::Drawing::Point(337, 219);
			this->c6->Name = L"c6";
			this->c6->Size = System::Drawing::Size(64, 64);
			this->c6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->c6->TabIndex = 139;
			this->c6->TabStop = false;
			// 
			// b6
			// 
			this->b6->BackColor = System::Drawing::Color::Black;
			this->b6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b6->Location = System::Drawing::Point(273, 219);
			this->b6->Name = L"b6";
			this->b6->Size = System::Drawing::Size(64, 64);
			this->b6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->b6->TabIndex = 138;
			this->b6->TabStop = false;
			// 
			// a6
			// 
			this->a6->BackColor = System::Drawing::Color::White;
			this->a6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a6->Location = System::Drawing::Point(209, 219);
			this->a6->Name = L"a6";
			this->a6->Size = System::Drawing::Size(64, 64);
			this->a6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->a6->TabIndex = 137;
			this->a6->TabStop = false;
			// 
			// h7
			// 
			this->h7->BackColor = System::Drawing::Color::White;
			this->h7->Location = System::Drawing::Point(657, 155);
			this->h7->Name = L"h7";
			this->h7->Size = System::Drawing::Size(64, 64);
			this->h7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->h7->TabIndex = 136;
			this->h7->TabStop = false;
			// 
			// g7
			// 
			this->g7->BackColor = System::Drawing::Color::Black;
			this->g7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g7->Location = System::Drawing::Point(593, 155);
			this->g7->Name = L"g7";
			this->g7->Size = System::Drawing::Size(64, 64);
			this->g7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->g7->TabIndex = 135;
			this->g7->TabStop = false;
			// 
			// f7
			// 
			this->f7->BackColor = System::Drawing::Color::White;
			this->f7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f7->Location = System::Drawing::Point(529, 155);
			this->f7->Name = L"f7";
			this->f7->Size = System::Drawing::Size(64, 64);
			this->f7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->f7->TabIndex = 134;
			this->f7->TabStop = false;
			// 
			// e7
			// 
			this->e7->BackColor = System::Drawing::Color::Black;
			this->e7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e7->Location = System::Drawing::Point(465, 155);
			this->e7->Name = L"e7";
			this->e7->Size = System::Drawing::Size(64, 64);
			this->e7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->e7->TabIndex = 133;
			this->e7->TabStop = false;
			// 
			// d7
			// 
			this->d7->BackColor = System::Drawing::Color::White;
			this->d7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d7->Location = System::Drawing::Point(401, 155);
			this->d7->Name = L"d7";
			this->d7->Size = System::Drawing::Size(64, 64);
			this->d7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->d7->TabIndex = 132;
			this->d7->TabStop = false;
			// 
			// c7
			// 
			this->c7->BackColor = System::Drawing::Color::Black;
			this->c7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c7->Location = System::Drawing::Point(337, 155);
			this->c7->Name = L"c7";
			this->c7->Size = System::Drawing::Size(64, 64);
			this->c7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->c7->TabIndex = 131;
			this->c7->TabStop = false;
			// 
			// b7
			// 
			this->b7->BackColor = System::Drawing::Color::White;
			this->b7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b7->Location = System::Drawing::Point(273, 155);
			this->b7->Name = L"b7";
			this->b7->Size = System::Drawing::Size(64, 64);
			this->b7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->b7->TabIndex = 130;
			this->b7->TabStop = false;
			// 
			// a7
			// 
			this->a7->BackColor = System::Drawing::Color::Black;
			this->a7->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a7->Location = System::Drawing::Point(209, 155);
			this->a7->Name = L"a7";
			this->a7->Size = System::Drawing::Size(64, 64);
			this->a7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->a7->TabIndex = 129;
			this->a7->TabStop = false;
			// 
			// h8
			// 
			this->h8->BackColor = System::Drawing::Color::Black;
			this->h8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->h8->Location = System::Drawing::Point(657, 91);
			this->h8->Name = L"h8";
			this->h8->Size = System::Drawing::Size(64, 64);
			this->h8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->h8->TabIndex = 128;
			this->h8->TabStop = false;
			// 
			// g8
			// 
			this->g8->BackColor = System::Drawing::Color::White;
			this->g8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->g8->Location = System::Drawing::Point(593, 91);
			this->g8->Name = L"g8";
			this->g8->Size = System::Drawing::Size(64, 64);
			this->g8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->g8->TabIndex = 127;
			this->g8->TabStop = false;
			// 
			// f8
			// 
			this->f8->BackColor = System::Drawing::Color::Black;
			this->f8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->f8->Location = System::Drawing::Point(529, 91);
			this->f8->Name = L"f8";
			this->f8->Size = System::Drawing::Size(64, 64);
			this->f8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->f8->TabIndex = 126;
			this->f8->TabStop = false;
			// 
			// e8
			// 
			this->e8->BackColor = System::Drawing::Color::White;
			this->e8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->e8->Location = System::Drawing::Point(465, 91);
			this->e8->Name = L"e8";
			this->e8->Size = System::Drawing::Size(64, 64);
			this->e8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->e8->TabIndex = 125;
			this->e8->TabStop = false;
			// 
			// d8
			// 
			this->d8->BackColor = System::Drawing::Color::Black;
			this->d8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->d8->Location = System::Drawing::Point(401, 91);
			this->d8->Name = L"d8";
			this->d8->Size = System::Drawing::Size(64, 64);
			this->d8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->d8->TabIndex = 124;
			this->d8->TabStop = false;
			// 
			// c8
			// 
			this->c8->BackColor = System::Drawing::Color::White;
			this->c8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->c8->Location = System::Drawing::Point(337, 91);
			this->c8->Name = L"c8";
			this->c8->Size = System::Drawing::Size(64, 64);
			this->c8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->c8->TabIndex = 123;
			this->c8->TabStop = false;
			// 
			// b8
			// 
			this->b8->BackColor = System::Drawing::Color::Black;
			this->b8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->b8->Location = System::Drawing::Point(273, 91);
			this->b8->Name = L"b8";
			this->b8->Size = System::Drawing::Size(64, 64);
			this->b8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->b8->TabIndex = 122;
			this->b8->TabStop = false;
			// 
			// a8
			// 
			this->a8->BackColor = System::Drawing::Color::White;
			this->a8->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->a8->Location = System::Drawing::Point(209, 91);
			this->a8->Name = L"a8";
			this->a8->Size = System::Drawing::Size(64, 64);
			this->a8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->a8->TabIndex = 121;
			this->a8->TabStop = false;
			// 
			// blackPawn
			// 
			this->blackPawn->AllowDrop = true;
			this->blackPawn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"blackPawn.BackgroundImage")));
			this->blackPawn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->blackPawn->Location = System::Drawing::Point(599, 626);
			this->blackPawn->Name = L"blackPawn";
			this->blackPawn->Size = System::Drawing::Size(57, 57);
			this->blackPawn->TabIndex = 120;
			this->blackPawn->UseVisualStyleBackColor = true;
			// 
			// blackKnight
			// 
			this->blackKnight->AllowDrop = true;
			this->blackKnight->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"blackKnight.BackgroundImage")));
			this->blackKnight->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->blackKnight->Location = System::Drawing::Point(536, 625);
			this->blackKnight->Name = L"blackKnight";
			this->blackKnight->Size = System::Drawing::Size(57, 57);
			this->blackKnight->TabIndex = 119;
			this->blackKnight->UseVisualStyleBackColor = true;
			// 
			// blackBishop
			// 
			this->blackBishop->AllowDrop = true;
			this->blackBishop->BackColor = System::Drawing::SystemColors::Control;
			this->blackBishop->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"blackBishop.BackgroundImage")));
			this->blackBishop->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->blackBishop->Location = System::Drawing::Point(473, 625);
			this->blackBishop->Name = L"blackBishop";
			this->blackBishop->Size = System::Drawing::Size(57, 57);
			this->blackBishop->TabIndex = 118;
			this->blackBishop->UseVisualStyleBackColor = false;
			// 
			// blackRoof
			// 
			this->blackRoof->AllowDrop = true;
			this->blackRoof->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"blackRoof.BackgroundImage")));
			this->blackRoof->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->blackRoof->Location = System::Drawing::Point(406, 625);
			this->blackRoof->Name = L"blackRoof";
			this->blackRoof->Size = System::Drawing::Size(51, 57);
			this->blackRoof->TabIndex = 117;
			this->blackRoof->UseVisualStyleBackColor = true;
			// 
			// blackQueen
			// 
			this->blackQueen->AllowDrop = true;
			this->blackQueen->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"blackQueen.BackgroundImage")));
			this->blackQueen->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->blackQueen->Location = System::Drawing::Point(337, 625);
			this->blackQueen->Name = L"blackQueen";
			this->blackQueen->Size = System::Drawing::Size(63, 57);
			this->blackQueen->TabIndex = 116;
			this->blackQueen->UseVisualStyleBackColor = true;
			// 
			// blackKing
			// 
			this->blackKing->AllowDrop = true;
			this->blackKing->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"blackKing.BackgroundImage")));
			this->blackKing->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->blackKing->ForeColor = System::Drawing::SystemColors::ButtonShadow;
			this->blackKing->Location = System::Drawing::Point(274, 625);
			this->blackKing->Name = L"blackKing";
			this->blackKing->Size = System::Drawing::Size(57, 57);
			this->blackKing->TabIndex = 115;
			this->blackKing->UseVisualStyleBackColor = true;
			// 
			// whitePawn
			// 
			this->whitePawn->AllowDrop = true;
			this->whitePawn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"whitePawn.BackgroundImage")));
			this->whitePawn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->whitePawn->Location = System::Drawing::Point(598, 27);
			this->whitePawn->Name = L"whitePawn";
			this->whitePawn->Size = System::Drawing::Size(57, 58);
			this->whitePawn->TabIndex = 114;
			this->whitePawn->UseVisualStyleBackColor = true;
			// 
			// whiteKnight
			// 
			this->whiteKnight->AllowDrop = true;
			this->whiteKnight->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"whiteKnight.BackgroundImage")));
			this->whiteKnight->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->whiteKnight->Location = System::Drawing::Point(535, 27);
			this->whiteKnight->Name = L"whiteKnight";
			this->whiteKnight->Size = System::Drawing::Size(57, 57);
			this->whiteKnight->TabIndex = 113;
			this->whiteKnight->UseVisualStyleBackColor = true;
			// 
			// whiteBishop
			// 
			this->whiteBishop->AllowDrop = true;
			this->whiteBishop->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"whiteBishop.BackgroundImage")));
			this->whiteBishop->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->whiteBishop->Location = System::Drawing::Point(472, 27);
			this->whiteBishop->Name = L"whiteBishop";
			this->whiteBishop->Size = System::Drawing::Size(57, 57);
			this->whiteBishop->TabIndex = 112;
			this->whiteBishop->UseVisualStyleBackColor = true;
			// 
			// whiteRoof
			// 
			this->whiteRoof->AllowDrop = true;
			this->whiteRoof->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"whiteRoof.BackgroundImage")));
			this->whiteRoof->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->whiteRoof->Location = System::Drawing::Point(405, 28);
			this->whiteRoof->Name = L"whiteRoof";
			this->whiteRoof->Size = System::Drawing::Size(51, 57);
			this->whiteRoof->TabIndex = 111;
			this->whiteRoof->UseVisualStyleBackColor = true;
			// 
			// whiteQueen
			// 
			this->whiteQueen->AllowDrop = true;
			this->whiteQueen->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"whiteQueen.BackgroundImage")));
			this->whiteQueen->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->whiteQueen->Location = System::Drawing::Point(336, 27);
			this->whiteQueen->Name = L"whiteQueen";
			this->whiteQueen->Size = System::Drawing::Size(63, 57);
			this->whiteQueen->TabIndex = 110;
			this->whiteQueen->UseVisualStyleBackColor = true;
			// 
			// whiteKing
			// 
			this->whiteKing->AllowDrop = true;
			this->whiteKing->BackColor = System::Drawing::SystemColors::Control;
			this->whiteKing->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"whiteKing.BackgroundImage")));
			this->whiteKing->FlatAppearance->BorderColor = System::Drawing::SystemColors::Control;
			this->whiteKing->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->whiteKing->Location = System::Drawing::Point(273, 27);
			this->whiteKing->Name = L"whiteKing";
			this->whiteKing->Size = System::Drawing::Size(57, 57);
			this->whiteKing->TabIndex = 109;
			this->whiteKing->UseVisualStyleBackColor = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ôàéëToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(924, 24);
			this->menuStrip1->TabIndex = 202;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ChessBoardEditor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Info;
			this->ClientSize = System::Drawing::Size(924, 685);
			this->Controls->Add(this->clearButton);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->h1);
			this->Controls->Add(this->g1);
			this->Controls->Add(this->f1);
			this->Controls->Add(this->e1);
			this->Controls->Add(this->d1);
			this->Controls->Add(this->c1);
			this->Controls->Add(this->b1);
			this->Controls->Add(this->a1);
			this->Controls->Add(this->h2);
			this->Controls->Add(this->g2);
			this->Controls->Add(this->f2);
			this->Controls->Add(this->e2);
			this->Controls->Add(this->d2);
			this->Controls->Add(this->c2);
			this->Controls->Add(this->b2);
			this->Controls->Add(this->a2);
			this->Controls->Add(this->h3);
			this->Controls->Add(this->g3);
			this->Controls->Add(this->f3);
			this->Controls->Add(this->e3);
			this->Controls->Add(this->d3);
			this->Controls->Add(this->c3);
			this->Controls->Add(this->b3);
			this->Controls->Add(this->a3);
			this->Controls->Add(this->h4);
			this->Controls->Add(this->g4);
			this->Controls->Add(this->f4);
			this->Controls->Add(this->e4);
			this->Controls->Add(this->d4);
			this->Controls->Add(this->c4);
			this->Controls->Add(this->b4);
			this->Controls->Add(this->a4);
			this->Controls->Add(this->h5);
			this->Controls->Add(this->g5);
			this->Controls->Add(this->f5);
			this->Controls->Add(this->e5);
			this->Controls->Add(this->d5);
			this->Controls->Add(this->c5);
			this->Controls->Add(this->b5);
			this->Controls->Add(this->a5);
			this->Controls->Add(this->h6);
			this->Controls->Add(this->g6);
			this->Controls->Add(this->f6);
			this->Controls->Add(this->e6);
			this->Controls->Add(this->d6);
			this->Controls->Add(this->c6);
			this->Controls->Add(this->b6);
			this->Controls->Add(this->a6);
			this->Controls->Add(this->h7);
			this->Controls->Add(this->g7);
			this->Controls->Add(this->f7);
			this->Controls->Add(this->e7);
			this->Controls->Add(this->d7);
			this->Controls->Add(this->c7);
			this->Controls->Add(this->b7);
			this->Controls->Add(this->a7);
			this->Controls->Add(this->h8);
			this->Controls->Add(this->g8);
			this->Controls->Add(this->f8);
			this->Controls->Add(this->e8);
			this->Controls->Add(this->d8);
			this->Controls->Add(this->c8);
			this->Controls->Add(this->b8);
			this->Controls->Add(this->a8);
			this->Controls->Add(this->blackPawn);
			this->Controls->Add(this->blackKnight);
			this->Controls->Add(this->blackBishop);
			this->Controls->Add(this->blackRoof);
			this->Controls->Add(this->blackQueen);
			this->Controls->Add(this->blackKing);
			this->Controls->Add(this->whitePawn);
			this->Controls->Add(this->whiteKnight);
			this->Controls->Add(this->whiteBishop);
			this->Controls->Add(this->whiteRoof);
			this->Controls->Add(this->whiteQueen);
			this->Controls->Add(this->whiteKing);
			this->Controls->Add(this->menuStrip1);
			this->ForeColor = System::Drawing::Color::Black;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"ChessBoardEditor";
			this->Text = L"ChessGame";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->h8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->g8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->f8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->e8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->d8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->c8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->b8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->a8))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	};
	public ref class Figure
	{
	public: String^ location;
	public: String^ name;
	public: String^ color;
	};
}
