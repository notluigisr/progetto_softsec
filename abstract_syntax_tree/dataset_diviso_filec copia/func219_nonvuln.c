    void CloneUser(const CString& sLine) {
        if (!GetUser()->IsAdmin()) {
            PutModule(
                t_s("STR"));
            return;
        }

        const CString sOldUsername = sLine.Token(1),
                      sNewUsername = sLine.Token(2, true);

        if (sOldUsername.empty() || sNewUsername.empty()) {
            PutModule(t_s("STR"));
            return;
        }

        CUser* pOldUser = CZNC::Get().FindUser(sOldUsername);

        if (!pOldUser) {
            PutModule(t_f("STR")(sOldUsername));
            return;
        }

        CUser* pNewUser = new CUser(sNewUsername);
        CString sError;
        if (!pNewUser->Clone(*pOldUser, sError)) {
            delete pNewUser;
            PutModule(t_f("STR")(sError));
            return;
        }

        if (!CZNC::Get().AddUser(pNewUser, sError)) {
            delete pNewUser;
            PutModule(t_f("STR")(sError));
            return;
        }

        PutModule(t_f("STR")(sNewUsername));
        return;
    }