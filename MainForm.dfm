object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1043#1083#1072#1074#1085#1086#1077' '#1086#1082#1085#1086
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  TextHeight = 15
  object MainMenu1: TMainMenu
    Left = 32
    object FileMenu: TMenuItem
      Caption = #1060#1072#1081#1083
      object OpenItem: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = OpenItemClick
      end
    end
    object WindowMenu: TMenuItem
      Caption = #1054#1082#1085#1086
    end
  end
  object OpenDialog: TOpenDialog
    Left = 200
    Top = 96
  end
end
