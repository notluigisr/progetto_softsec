bool CClient::OnTextMessage(CTextMessage& Message) {
    CString sTargets = Message.GetTarget();

    VCString vTargets;
    sTargets.Split("STR", vTargets, false);

    for (CString& sTarget : vTargets) {
        Message.SetTarget(sTarget);
        if (m_pNetwork) {
            
            Message.SetChan(m_pNetwork->FindChan(sTarget));
        }

        if (sTarget.TrimPrefix(m_pUser->GetStatusPrefix())) {
            if (sTarget.Equals("STR")) {
                CString sMsg = Message.GetText();
                UserCommand(sMsg);
            } else {
                CALLMOD(sTarget, this, m_pUser, m_pNetwork,
                        OnModCommand(Message.GetText()));
            }
            continue;
        }

        bool bContinue = false;
        NETWORKMODULECALL(OnUserTextMessage(Message), m_pUser, m_pNetwork, this,
                          &bContinue);
        if (bContinue) continue;

        if (!GetIRCSock()) {
            
            if (!sTarget.Equals(m_sNick))
                PutStatus(
                    t_f("STR"
                        "STR")(Message.GetTarget()));
            continue;
        }

        if (m_pNetwork) {
            AddBuffer(Message);
            EchoMessage(Message);
            PutIRC(Message.ToString(CMessage::ExcludePrefix |
                                    CMessage::ExcludeTags));
        }
    }

    return true;
}