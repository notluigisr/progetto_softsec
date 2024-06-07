std::wstring CreateUniqueTempDirectory()
{
    
    
    
    
    
    
    wchar_t tmpdir[MAX_PATH+1];
    if ( GetTempPath(MAX_PATH+1, tmpdir) == 0 )
        throw Win32Exception("STR");

    for ( ;; )
    {
        std::wstring dir(tmpdir);
        dir += L"STR";

        UUID uuid;
        UuidCreate(&uuid);
        RPC_WSTR uuidStr;
        RPC_STATUS status = UuidToString(&uuid, &uuidStr);
        dir += reinterpret_cast<wchar_t*>(uuidStr);
        RpcStringFree(&uuidStr);

        if ( CreateDirectory(dir.c_str(), NULL) )
            return dir;
        else if ( GetLastError() != ERROR_ALREADY_EXISTS )
            throw Win32Exception("STR");
    }
}