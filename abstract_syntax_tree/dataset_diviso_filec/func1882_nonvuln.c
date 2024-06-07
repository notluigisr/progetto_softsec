bool CIRCSock::OnModeMessage(CModeMessage& Message) {
    const CNick& Nick = Message.GetNick();
    CString sTarget = Message.GetTarget();
    CString sModes = Message.GetModes();

    CChan* pChan = m_pNetwork->FindChan(sTarget);
    if (pChan) {
        pChan->ModeChange(sModes, &Nick);

        if (pChan->IsDetached()) {
            return true;
        }
    } else if (sTarget == m_Nick.GetNick()) {
        CString sModeArg = sModes.Token(0);
        bool bAdd = true;
        
        for (unsigned int a = 0; a < sModeArg.size(); a++) {
            const char& cMode = sModeArg[a];

            if (cMode == '+') {
                bAdd = true;
            } else if (cMode == '-') {
                bAdd = false;
            } else {
                if (bAdd) {
                    m_scUserModes.insert(cMode);
                } else {
                    m_scUserModes.erase(cMode);
                }
            }
        }
    }
    return false;
}