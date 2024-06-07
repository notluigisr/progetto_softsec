UnicodeString __fastcall TSaveSessionDialog::GetSessionName()
{
  UnicodeString Folder;
  if (FolderCombo->Text != FRootFolder)
  {
    Folder = FolderCombo->Text;
  }
  return TSessionData::ComposePath(Folder, SessionNameEdit->Text);
}