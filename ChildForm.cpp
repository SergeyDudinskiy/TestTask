#include <algorithm>

#include "ChildForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

TChildForm* ChildForm;

__fastcall TChildForm::TChildForm(TComponent* Owner) : TForm(Owner), fScale(1.0f)
{
    fBitmap = new Graphics::TBitmap();

    ScrollBox->HorzScrollBar->Tracking = true;
    ScrollBox->VertScrollBar->Tracking = true;
    ScrollBox->OnMouseWheel = ScrollBoxMouseWheel;

    PaintBox->Align = alNone;
    PaintBox->Parent = ScrollBox;
    PaintBox->OnPaint = PaintBoxPaint;
    PaintBox->OnMouseMove = PaintBoxMouseMove;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::FormClose(TObject* Sender, TCloseAction& Action)
{
    Action = caFree;
    delete fBitmap;
}
//---------------------------------------------------------------------------
void TChildForm::LoadImage(const String& fileName)
{
    if (!FileExists(fileName)) {
        ShowMessage("Файл не существует: " + fileName);
        return;
    }

    try {
        String lowerFileName = fileName.LowerCase();

        if (lowerFileName.Pos(".bmp") == lowerFileName.Length() - 3)
            fBitmap->LoadFromFile(fileName);
        else if (lowerFileName.Pos(".jpg") == lowerFileName.Length() - 3 ||
                 lowerFileName.Pos(".jpeg") == lowerFileName.Length() - 4) {
            TJPEGImage* jpeg = new TJPEGImage();

            try {
                jpeg->LoadFromFile(fileName);
                fBitmap->Assign(jpeg);
            }
            __finally {
                delete jpeg;
            }
        }
        else {
            ShowMessage("Неподдерживаемый формат файла: " + fileName);
            return;
        }

        AdjustPaintBoxSize();
        UpdateScrollBars();
    }
    catch (Exception& e) {
        ShowMessage("Ошибка при загрузке изображения: " + e.Message);
    }
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::PaintBoxPaint(TObject* Sender)
{
    TRect destRect;

    if (PaintBox->Width <= ScrollBox->ClientWidth && PaintBox->Height <= ScrollBox->ClientHeight) {
        int offsetX = (ScrollBox->ClientWidth - PaintBox->Width) / 2;
        int offsetY = (ScrollBox->ClientHeight - PaintBox->Height) / 2;
        destRect = TRect(offsetX, offsetY, offsetX + PaintBox->Width, offsetY + PaintBox->Height);
    }
    else {
        destRect = TRect(0, 0, PaintBox->Width, PaintBox->Height);
    }

    PaintBox->Canvas->StretchDraw(destRect, fBitmap);
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::FormResize(TObject* Sender)
{
    AdjustPaintBoxSize();
    UpdateScrollBars();
    PaintBox->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::ScrollBoxMouseWheel(TObject* Sender, TShiftState Shift, int WheelDelta, const TPoint& MousePos, bool& Handled)
{
    float oldScale = fScale;

    if (WheelDelta > 0)
        fScale = std::min(fScale + 0.1f, 10.0f); //максимальный масштаб 1000%
    else
        fScale = std::max(fScale - 0.1f, 0.2f); //минимальный масштаб 20%

    //обновляем размер PaintBox и полос прокрутки
    AdjustPaintBoxSize();
    UpdateScrollBars();

    //корректируем позицию прокрутки, чтобы точка под курсором осталась на месте
    AdjustScrollPosition(oldScale);

    PaintBox->Invalidate();
    Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::PaintBoxMouseMove(TObject* Sender, TShiftState Shift, int X, int Y)
{
    //запоминаем позицию курсора относительно изображения
    fCursorPos = TPoint(X, Y);
}
//---------------------------------------------------------------------------
void TChildForm::AdjustPaintBoxSize()
{
    PaintBox->Width = fBitmap->Width * fScale;
    PaintBox->Height = fBitmap->Height * fScale;
}
//---------------------------------------------------------------------------
void TChildForm::UpdateScrollBars()
{
    ScrollBox->HorzScrollBar->Range = PaintBox->Width;
    ScrollBox->VertScrollBar->Range = PaintBox->Height;

    ScrollBox->HorzScrollBar->Visible = (PaintBox->Width > ScrollBox->ClientWidth);
    ScrollBox->VertScrollBar->Visible = (PaintBox->Height > ScrollBox->ClientHeight);
}
//---------------------------------------------------------------------------
void TChildForm::AdjustScrollPosition(float oldScale)
{
    //вычисляем новые координаты точки под курсором после изменения масштаба
    double newX = fCursorPos.x * (fScale / oldScale);
    double newY = fCursorPos.y * (fScale / oldScale);

    //вычисляем смещение для прокрутки
    double offsetX = newX - fCursorPos.x;
    double offsetY = newY - fCursorPos.y;

    //учитываем текущую позицию прокрутки
    double currentScrollX = ScrollBox->HorzScrollBar->Position;
    double currentScrollY = ScrollBox->VertScrollBar->Position;

    //вычисляем новую позицию прокрутки
    double newScrollX = currentScrollX + offsetX;
    double newScrollY = currentScrollY + offsetY;

    //округляем новую позицию прокрутки
    int roundedScrollX = static_cast<int>(round(newScrollX));
    int roundedScrollY = static_cast<int>(round(newScrollY));

    //устанавливаем новую позицию прокрутки
    ScrollBox->HorzScrollBar->Position = roundedScrollX;
    ScrollBox->VertScrollBar->Position = roundedScrollY;
}
