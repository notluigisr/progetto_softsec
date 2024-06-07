void CIRCNetwork::Clone(const CIRCNetwork& Network, bool bCloneName) {
    if (bCloneName) {
        m_sName = Network.GetName();
    }

    m_fFloodRate = Network.GetFloodRate();
    m_uFloodBurst = Network.GetFloodBurst();
    m_uJoinDelay = Network.GetJoinDelay();

    SetNick(Network.GetNick());
    SetAltNick(Network.GetAltNick());
    SetIdent(Network.GetIdent());
    SetRealName(Network.GetRealName());
    SetBindHost(Network.GetBindHost());
    SetEncoding(Network.GetEncoding());
    SetQuitMsg(Network.GetQuitMsg());
    m_ssTrustedFingerprints = Network.m_ssTrustedFingerprints;

    
    const vector<CServer*>& vServers = Network.GetServers();
    CString sServer;
    CServer* pCurServ = GetCurrentServer();

    if (pCurServ) {
        sServer = pCurServ->GetName();
    }

    DelServers();

    for (CServer* pServer : vServers) {
        AddServer(pServer->GetName(), pServer->GetPort(), pServer->GetPass(),
                  pServer->IsSSL());
    }

    m_uServerIdx = 0;
    for (size_t a = 0; a < m_vServers.size(); a++) {
        if (sServer.Equals(m_vServers[a]->GetName())) {
            m_uServerIdx = a + 1;
            break;
        }
    }
    if (m_uServerIdx == 0) {
        m_uServerIdx = m_vServers.size();
        CIRCSock* pSock = GetIRCSock();

        if (pSock) {
            PutStatus(
                t_s("STR"
                    "STR"));
            pSock->Quit();
        }
    }
    

    
    const vector<CChan*>& vChans = Network.GetChans();
    for (CChan* pNewChan : vChans) {
        CChan* pChan = FindChan(pNewChan->GetName());

        if (pChan) {
            pChan->SetInConfig(pNewChan->InConfig());
        } else {
            AddChan(pNewChan->GetName(), pNewChan->InConfig());
        }
    }

    for (CChan* pChan : m_vChans) {
        CChan* pNewChan = Network.FindChan(pChan->GetName());

        if (!pNewChan) {
            pChan->SetInConfig(false);
        } else {
            pChan->Clone(*pNewChan);
        }
    }
    

    
    set<CString> ssUnloadMods;
    CModules& vCurMods = GetModules();
    const CModules& vNewMods = Network.GetModules();

    for (CModule* pNewMod : vNewMods) {
        CString sModRet;
        CModule* pCurMod = vCurMods.FindModule(pNewMod->GetModName());

        if (!pCurMod) {
            vCurMods.LoadModule(pNewMod->GetModName(), pNewMod->GetArgs(),
                                CModInfo::NetworkModule, m_pUser, this,
                                sModRet);
        } else if (pNewMod->GetArgs() != pCurMod->GetArgs()) {
            vCurMods.ReloadModule(pNewMod->GetModName(), pNewMod->GetArgs(),
                                  m_pUser, this, sModRet);
        }
    }

    for (CModule* pCurMod : vCurMods) {
        CModule* pNewMod = vNewMods.FindModule(pCurMod->GetModName());

        if (!pNewMod) {
            ssUnloadMods.insert(pCurMod->GetModName());
        }
    }

    for (const CString& sMod : ssUnloadMods) {
        vCurMods.UnloadModule(sMod);
    }
    

    SetIRCConnectEnabled(Network.GetIRCConnectEnabled());
}