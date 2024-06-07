CString CWebSock::GetSkinPath(const CString& sSkinName) {
    CString sRet = CZNC::Get().GetZNCPath() + "STR" + sSkinName;

    if (!CFile::IsDir(sRet)) {
        sRet = CZNC::Get().GetCurPath() + "STR" + sSkinName;

        if (!CFile::IsDir(sRet)) {
            sRet = CString(_SKINDIR_) + "STR" + sSkinName;
        }
    }

    return sRet + "STR";
}