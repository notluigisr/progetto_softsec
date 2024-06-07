    void AuthorizationSession::_acquirePrivilegesForPrincipalFromDatabase(
            const std::string& dbname, const UserName& user) {

        BSONObj privilegeDocument;
        Status status = _externalState->getAuthorizationManager().getPrivilegeDocument(
                dbname, user, &privilegeDocument);
        if (status.isOK()) {
            status = acquirePrivilegesFromPrivilegeDocument(dbname, user, privilegeDocument);
        }
        if (!status.isOK() && status != ErrorCodes::UserNotFound) {
            log() << "STR" <<
                dbname << "STR" << endl;
        }
    }