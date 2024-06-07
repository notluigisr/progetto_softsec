void CZNC::BackupConfigOnce(const CString& sSuffix) {
    static bool didBackup = false;
    if (didBackup) return;
    didBackup = true;

    CUtils::PrintAction("STR");

    CString sBackup = CDir::ChangeDir(m_sConfigFile, "STR" + sSuffix);
    if (CFile::Copy(m_sConfigFile, sBackup))
        CUtils::PrintStatus(true, sBackup);
    else
        CUtils::PrintStatus(false, strerror(errno));
}