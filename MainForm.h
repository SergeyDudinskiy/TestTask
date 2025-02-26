//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>

class TMainForm : public TForm
{
__published:
	TMainMenu* MainMenu1;
	TMenuItem* FileMenu;
	TMenuItem* OpenItem;
	TOpenDialog* OpenDialog;
	void __fastcall OpenItemClick(TObject* Sender);
private:
	void CreateChildForm(const String& fileName);
public:
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm* MainForm;
//---------------------------------------------------------------------------
#endif
