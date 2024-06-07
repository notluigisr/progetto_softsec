    Status AuthorizationManager::acquirePrivilegesFromPrivilegeDocument(
            const std::string& dbname, const PrincipalName& principal, const BSONObj& privilegeDocument) {
        if (!_authenticatedPrincipals.lookup(principal)) {
            return Status(ErrorCodes::UserNotFound,
                          mongoutils::str::stream()
                                  << "STR"
                                  << principal.getUser()
                                  << "STR"
                                  << principal.getDB(),
                          0);
        }
        if (principal.getUser() == internalSecurity.user) {
            
            ActionSet allActions;
            allActions.addAllActions();
            return acquirePrivilege(Privilege(PrivilegeSet::WILDCARD_RESOURCE, allActions),
                                    principal);
        }
        return buildPrivilegeSet(dbname, principal, privilegeDocument, &_acquiredPrivileges);
    }