bool CModules::OnServerCapAvailable(const CString& sCap) {
    bool bResult = false;
    for (CModule* pMod : *this) {
        try {
            CClient* pOldClient = pMod->GetClient();
            pMod->SetClient(m_pClient);
            if (m_pUser) {
                CUser* pOldUser = pMod->GetUser();
                pMod->SetUser(m_pUser);
                bResult |= pMod->OnServerCapAvailable(sCap);
                pMod->SetUser(pOldUser);
            } else {
                
                bResult |= pMod->OnServerCapAvailable(sCap);
            }
            pMod->SetClient(pOldClient);
        } catch (const CModule::EModException& e) {
            if (CModule::UNLOAD == e) {
                UnloadModule(pMod->GetModName());
            }
        }
    }
    return bResult;
}