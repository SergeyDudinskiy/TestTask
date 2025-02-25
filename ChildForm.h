//---------------------------------------------------------------------------
#ifndef ChildFormH
#define ChildFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TChildForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TChildForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChildForm* ChildForm;
//---------------------------------------------------------------------------
#endif
