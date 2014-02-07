#include "SignalWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
System::Void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	SignalUtility::SignalWindow form;
	Application::Run(%form);
}