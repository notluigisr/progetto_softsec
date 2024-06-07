WCHAR* VDir::MapPathW(const WCHAR *pInName)
{   
    WCHAR szBuffer[(MAX_PATH+1)*2];
    WCHAR szlBuf[MAX_PATH+1];
    int length = wcslen(pInName);

    if (!length)
	return (WCHAR*)pInName;

    if (length > MAX_PATH) {
	wcsncpy(szlBuf, pInName, MAX_PATH);
	if (IsPathSep(pInName[0]) && !IsPathSep(pInName[1])) {   
	    
	    szlBuf[MAX_PATH-2] = '\0';
	}
	else
	    szlBuf[MAX_PATH] = '\0';
	pInName = szlBuf;
    }
    

    if (pInName[1] == ':') {
	
	if (IsPathSep(pInName[2])) {
	    
	    DoGetFullPathNameW((WCHAR*)pInName, (sizeof(szLocalBufferW)/sizeof(WCHAR)), szLocalBufferW);
	}
	else {
	    
	    wcscpy(szBuffer, GetDirW(DriveIndex((char)*pInName)));
	    wcscat(szBuffer, &pInName[2]);
	    if(wcslen(szBuffer) > MAX_PATH)
		szBuffer[MAX_PATH] = '\0';

	    DoGetFullPathNameW(szBuffer, (sizeof(szLocalBufferW)/sizeof(WCHAR)), szLocalBufferW);
	}
    }
    else {
	
	if (IsPathSep(pInName[1]) && IsPathSep(pInName[0])) {
	    
	    DoGetFullPathNameW((WCHAR*)pInName, (sizeof(szLocalBufferW)/sizeof(WCHAR)), szLocalBufferW);
	}
	else {
	    wcscpy(szBuffer, GetDefaultDirW());
	    if (IsPathSep(pInName[0])) {
		
		wcscpy(&szBuffer[2], pInName);
		DoGetFullPathNameW(szBuffer, (sizeof(szLocalBufferW)/sizeof(WCHAR)), szLocalBufferW);
	    }
	    else {
		
		if (IsSpecialFileName(pInName)) {
		    return (WCHAR*)pInName;
		}
		else {
		    wcscat(szBuffer, pInName);
		    if (wcslen(szBuffer) > MAX_PATH)
			szBuffer[MAX_PATH] = '\0';

		    DoGetFullPathNameW(szBuffer, (sizeof(szLocalBufferW)/sizeof(WCHAR)), szLocalBufferW);
		}
	    }
	}
    }
    return szLocalBufferW;
}