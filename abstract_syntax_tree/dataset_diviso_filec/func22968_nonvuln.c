const CString& CIRCNetwork::GetNick(const bool bAllowDefault) const {
    if (m_sNick.empty()) {
        return m_pUser->GetNick(bAllowDefault);
    }

    return m_sNick;
}