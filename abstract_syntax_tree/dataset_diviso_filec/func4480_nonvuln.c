void __fastcall TSaveSessionDialog::DoChange(bool & CanSubmit)
{
  CanSubmit = !SessionNameEdit->Text.IsEmpty();
  TCustomDialog::DoChange(CanSubmit);
}