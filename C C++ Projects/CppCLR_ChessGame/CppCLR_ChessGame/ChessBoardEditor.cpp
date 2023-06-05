#include "ChessBoardEditor.h"
#include "pch.h"
#include <string>
#include <Windows.h>
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;
using namespace System::Windows::Forms;

int main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    ChessGame::ChessBoardEditor form;
    Application::Run(% form);
    return 0;
}