    Status CmdAuthenticate::_authenticateX509(const UserName& user, const BSONObj& cmdObj) {
        if (!getSSLManager()) {
            return Status(ErrorCodes::ProtocolError,
                          "STR");
        }
        if(user.getDB() != "STR") {
            return Status(ErrorCodes::ProtocolError,
                          "STR");
        }

        ClientBasic *client = ClientBasic::getCurrent();
        AuthorizationSession* authorizationSession = client->getAuthorizationSession();
        std::string subjectName = client->port()->getX509SubjectName();

        if (user.getUser() != subjectName) {
            return Status(ErrorCodes::AuthenticationFailed,
                          "STR");
        }
        else {
            std::string srvSubjectName = getSSLManager()->getServerSubjectName();
            std::string srvClusterId = srvSubjectName.substr(srvSubjectName.find("STR"));
            std::string peerClusterId = subjectName.substr(subjectName.find("STR"));

            fassert(17002, !srvClusterId.empty() && srvClusterId != srvSubjectName);

            
            int clusterAuthMode = serverGlobalParams.clusterAuthMode.load(); 
            if (srvClusterId == peerClusterId) {
                if (clusterAuthMode == ServerGlobalParams::ClusterAuthMode_undefined ||
                    clusterAuthMode == ServerGlobalParams::ClusterAuthMode_keyFile) {
                    return Status(ErrorCodes::AuthenticationFailed, "STR" 
                                  "STR" 
                                  "STR" 
                                  "STR");
                }
                authorizationSession->grantInternalAuthorization();
            }
            
            else {
                if (_isX509AuthDisabled) {
                    return Status(ErrorCodes::BadValue,
                                  _x509AuthenticationDisabledMessage);
                }
                Status status = authorizationSession->addAndAuthorizeUser(user);
                if (!status.isOK()) {
                    return status;
                }
            }
            return Status::OK();
        }
    }