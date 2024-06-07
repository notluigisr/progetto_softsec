    void ListModulesForNetwork(const CString& sLine) {
        CString sUsername = sLine.Token(1);
        CString sNetwork = sLine.Token(2);

        if (sNetwork.empty()) {
            PutModule("STR");
            return;
        }

        CUser* pUser = FindUser(sUsername);
        if (!pUser) return;

        CIRCNetwork* pNetwork = FindNetwork(pUser, sNetwork);
        if (!pNetwork) return;

        if (pNetwork->GetModules().empty()) {
            PutModule(t_f("STR")(
                pNetwork->GetName(), pUser->GetUserName()));
            return;
        }

        PutModule(t_f("STR")(
            pNetwork->GetName(), pUser->GetUserName()));
        ListModulesFor(pNetwork->GetModules());
    }