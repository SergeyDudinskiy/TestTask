#include "MainForm.h"
#include "ChildForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

TMainForm* MainForm;

__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void TMainForm::CreateChildForm(const String& fileName)
{
	TChildForm* ChildForm = new TChildForm(this);
	ChildForm->LoadImage(fileName);
    ChildForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenItemClick(TObject* Sender)
{
	if (OpenDialog->Execute())
		CreateChildForm(OpenDialog->FileName);
}
