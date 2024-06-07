    Status AuthorizationSession::acquirePrivilegesFromPrivilegeDocument(
            const std::string& dbname, const UserName& user, const BSONObj& privilegeDocument) {
        if (!_authenticatedPrincipals.lookup(user)) {
            return Status(ErrorCodes::UserNotFound,
                          mongoutils::str::stream()
                                  << "STR"
                                  << user.getUser()
                                  << "STR"
                                  << user.getDB(),
                          0);
        }
        if (user.getUser() == internalSecurity.user) {
            
            ActionSet allActions;
            allActions.addAllActions();
            return acquirePrivilege(Privilege(PrivilegeSet::WILDCARD_RESOURCE, allActions), user);
        }
        return _externalState->getAuthorizationManager().buildPrivilegeSet(dbname,
                                                                           user,
                                                                           privilegeDocument,
                                                                           &_acquiredPrivileges);
    }