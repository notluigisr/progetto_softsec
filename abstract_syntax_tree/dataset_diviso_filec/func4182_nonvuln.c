bool CModule::PutUser(const CString& sLine) {
    return m_pNetwork ? m_pNetwork->PutUser(sLine, m_pClient) : false;
}