int __fastcall FingerprintScan(TConsole * Console, TProgramParams * Params)
{
  int Result = RESULT_SUCCESS;
  try
  {
    CheckLogParam(Params);

    std::unique_ptr<TSessionData> SessionData;

    if (Params->ParamCount > 0)
    {
      UnicodeString SessionUrl = Params->Param[1];
      bool DefaultsOnly;
      SessionData.reset(StoredSessions->ParseUrl(SessionUrl, Params, DefaultsOnly));
      if (DefaultsOnly || !SessionData->CanLogin ||
          (!SessionData->UsesSsh && (SessionData->Ftps == ftpsNone)))
      {
        SessionData.reset(NULL);
      }
    }

    if (!SessionData)
    {
      throw Exception(LoadStr(FINGERPRINTSCAN_NEED_SECURE_SESSION));
    }

    std::unique_ptr<TTerminal> Terminal(new TTerminal(SessionData.get(), Configuration));
    UnicodeString SHA256;
    UnicodeString SHA1;
    UnicodeString MD5;
    Terminal->FingerprintScan(SHA256, SHA1, MD5);
    if (!SHA256.IsEmpty())
    {
      Console->PrintLine(FORMAT(L"STR", (SHA256)));
    }
    if (!SHA1.IsEmpty())
    {
      Console->PrintLine(FORMAT(L"STR", (SHA1)));
    }
    if (!MD5.IsEmpty())
    {
      Console->PrintLine(FORMAT(L"STR", (MD5)));
    }
  }
  catch (Exception & E)
  {
    Result = HandleException(Console, E);
  }

  Console->WaitBeforeExit();
  return Result;
}