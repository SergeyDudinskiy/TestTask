//---------------------------------------------------------------------------
#ifndef ChildFormH
#define ChildFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <jpeg.hpp>

class TChildForm : public TForm
{
__published:
	TScrollBox* ScrollBox;
	TPaintBox* PaintBox;
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall PaintBoxPaint(TObject* Sender);
	void __fastcall FormResize(TObject* Sender);
    void __fastcall ScrollBoxMouseWheel(TObject* Sender, TShiftState Shift, int WheelDelta, const TPoint& MousePos, bool& Handled);
	void __fastcall PaintBoxMouseMove(TObject* Sender, TShiftState Shift, int X, int Y);
private:
	Graphics::TBitmap* fBitmap;
	float fScale;
	TPoint fCursorPos; //позиция курсора относительно изображения
    void UpdateScrollBars();
	void AdjustPaintBoxSize();
	void AdjustScrollPosition(float oldScale);
public:
    __fastcall TChildForm(TComponent* Owner);
    void LoadImage(const String& fileName);
};
#endif
