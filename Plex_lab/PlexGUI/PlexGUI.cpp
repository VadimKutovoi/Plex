#include "PlexGUI.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void Main(/*array<String^>^ args*/) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Plex_GUI::PlexGUI form;
	Application::Run(%form);
}
