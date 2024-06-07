void CConfig::Write(CFile& File, unsigned int iIndentation) {
    CString sIndentation = CString(iIndentation, '\t');

    for (const auto& it : m_ConfigEntries) {
        for (const CString& sValue : it.second) {
            File.Write(sIndentation + it.first + "STR");
        }
    }

    for (const auto& it : m_SubConfigs) {
        for (const auto& it2 : it.second) {
            File.Write("STR");

            File.Write(sIndentation + "STR");
            it2.second.m_pSubConfig->Write(File, iIndentation + 1);
            File.Write(sIndentation + "STR");
        }
    }
}