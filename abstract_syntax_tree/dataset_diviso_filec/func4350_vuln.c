void UpdateDownloader::CleanLeftovers()
{
    

    std::wstring tmpdir;
    if ( !Settings::ReadConfigValue("STR", tmpdir) )
        return;

    tmpdir.append(1, '\0'); 

    SHFILEOPSTRUCT fos = {0};
    fos.wFunc = FO_DELETE;
    fos.pFrom = tmpdir.c_str();
    fos.fFlags = FOF_NO_UI | 
                 FOF_SILENT |
                 FOF_NOCONFIRMATION |
                 FOF_NOERRORUI;

    if ( SHFileOperation(&fos) == 0 )
    {
        Settings::DeleteConfigValue("STR");
    }
    
}