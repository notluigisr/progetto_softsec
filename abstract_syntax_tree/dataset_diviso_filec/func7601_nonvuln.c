THistoryComboBox * __fastcall TCustomCommandOptionsDialog::CreateHistoryComboBox(
  const TCustomCommandType::TOption & Option, const UnicodeString & Value)
{
  THistoryComboBox * ComboBox = new THistoryComboBox(this);
  ComboBox->AutoComplete = false;
  AddComboBox(ComboBox, CreateLabel(Option.Caption));
  ComboBox->Items = CustomWinConfiguration->History[HistoryKey(Option)];
  ComboBox->Text = Value;
  return ComboBox;
}