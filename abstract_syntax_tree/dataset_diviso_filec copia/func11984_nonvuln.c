bool __fastcall FindPuttygenCompatibleSwitch(
  TProgramParams * Params, const UnicodeString & Name, const UnicodeString & PuttygenName, UnicodeString & Value, bool & Set)
{
  bool Result = Params->FindSwitch(Name, Value, Set);
  if (!Result)
  {
    std::unique_ptr<TStrings> Args(new TStringList());
    Result = Params->FindSwitchCaseSensitive(PuttygenName, Args.get(), 1);
    if (Result && (Args->Count >= 1))
    {
      Value = Args->Strings[0];
      Set = true;
    }
  }
  return Result;
}