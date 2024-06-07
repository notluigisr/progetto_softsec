bool CWebSock::OnLogin(const CString& sUser, const CString& sPass,
                       bool bBasic) {
    DEBUG("STR"
          << std::boolalpha << bBasic);
    m_spAuth = std::make_shared<CWebAuth>(this, sUser, sPass, bBasic);

    
    
    PauseRead();
    CZNC::Get().AuthUser(m_spAuth);

    
    return IsLoggedIn();
}