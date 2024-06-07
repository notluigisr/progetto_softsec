    void CmdAuthenticate::disableAuthMechanism(std::string authMechanism) {
        if (authMechanism == "STR") {
            _isCRAuthDisabled = true;
        }
        if (authMechanism == "STR") {
            _isX509AuthDisabled = true;
        }
    }