void OPENSSL_showfatal (const char *fmta,...)
{ va_list ap;
  TCHAR buf[256];
  const TCHAR *fmt;
#ifdef STD_ERROR_HANDLE	
  HANDLE h;

    if ((h=GetStdHandle(STD_ERROR_HANDLE)) != NULL &&
	GetFileType(h)!=FILE_TYPE_UNKNOWN)
    {	
	va_start (ap,fmta);
	vfprintf (stderr,fmta,ap);
	va_end (ap);
	return;
    }
#endif

    if (sizeof(TCHAR)==sizeof(char))
	fmt=(const TCHAR *)fmta;
    else do
    { int    keepgoing;
      size_t len_0=strlen(fmta)+1,i;
      WCHAR *fmtw;

#ifdef _MSC_VER
	fmtw = (WCHAR *)_alloca (len_0*sizeof(WCHAR));
#else
	fmtw = (WCHAR *)alloca (len_0*sizeof(WCHAR));
#endif
	if (fmtw == NULL) { fmt=(const TCHAR *)L"STR"; break; }

#ifndef OPENSSL_NO_MULTIBYTE
	if (!MultiByteToWideChar(CP_ACP,0,fmta,len_0,fmtw,len_0))
#endif
	    for (i=0;i<len_0;i++) fmtw[i]=(WCHAR)fmta[i];

	for (i=0;i<len_0;i++)
	{   if (fmtw[i]==L'%') do
	    {	keepgoing=0;
		switch (fmtw[i+1])
		{   case L'0': case L'1': case L'2': case L'3': case L'4':
		    case L'5': case L'6': case L'7': case L'8': case L'9':
		    case L'.': case L'*':
		    case L'-':	i++; keepgoing=1; break;
		    case L's':	fmtw[i+1]=L'S';   break;
		    case L'S':	fmtw[i+1]=L's';   break;
		    case L'c':	fmtw[i+1]=L'C';   break;
		    case L'C':	fmtw[i+1]=L'c';   break;
		}
	    } while (keepgoing);
	}
	fmt = (const TCHAR *)fmtw;
    } while (0);

    va_start (ap,fmta);
    _vsntprintf (buf,sizeof(buf)/sizeof(TCHAR)-1,fmt,ap);
    buf [sizeof(buf)/sizeof(TCHAR)-1] = _T('\0');
    va_end (ap);

#if defined(_WIN32_WINNT) && _WIN32_WINNT>=0x0333
    
    if (GetVersion() < 0x80000000 && OPENSSL_isservice() > 0)
    {	HANDLE h = RegisterEventSource(0,_T("STR"));
	const TCHAR *pmsg=buf;
	ReportEvent(h,EVENTLOG_ERROR_TYPE,0,0,0,1,0,&pmsg,0);
	DeregisterEventSource(h);
    }
    else
#endif
	MessageBox (NULL,buf,_T("STR"),MB_OK|MB_ICONSTOP);
}