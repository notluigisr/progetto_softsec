bool __fastcall TSaveSessionDialog::Execute(
  UnicodeString & SessionName, bool & SavePassword, bool & CreateShortcut,
  const UnicodeString & OriginalSessionName)
{
  FOriginalSessionName = OriginalSessionName;
  SessionNameEdit->Text = TSessionData::ExtractLocalName(SessionName);
  UnicodeString Folder = TSessionData::ExtractFolderName(SessionName);
  if (Folder.IsEmpty())
  {
    FolderCombo->Text = FRootFolder;
  }
  else
  {
    FolderCombo->Text = Folder;
  }
  SavePasswordCheck->Checked = SavePassword;
  CreateShortcutCheck->Checked = CreateShortcut;
  bool Result = TCustomDialog::Execute();
  if (Result)
  {
    SessionName = GetSessionName();
    SavePassword = SavePasswordCheck->Checked;
    CreateShortcut = CreateShortcutCheck->Checked;
  }
  return Result;
}