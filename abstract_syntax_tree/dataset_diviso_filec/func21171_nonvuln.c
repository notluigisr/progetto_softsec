void __fastcall TConsole::PrintLine(const UnicodeString & Str, bool Error)
{
  Print(Str + L"STR", false, Error);
};