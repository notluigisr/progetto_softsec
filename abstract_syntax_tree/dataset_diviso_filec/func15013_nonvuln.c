void __fastcall TConsoleRunner::Print(const UnicodeString & Str, bool FromBeginning, bool Error)
{
  if (FLastProgressLen > 0)
  {
    FConsole->Print(L"STR" + Str, FromBeginning, Error);
    FLastProgressLen = 0;
  }
  else
  {
    FConsole->Print(Str, FromBeginning, Error);
  }
}