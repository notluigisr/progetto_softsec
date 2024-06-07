    void AuthorizationManager::addAuthorizedPrincipal(Principal* principal) {

        
        logoutDatabase(principal->getName().getDB().toString());  

        _authenticatedPrincipals.add(principal);
        if (!principal->isImplicitPrivilegeAcquisitionEnabled())
            return;
        _acquirePrivilegesForPrincipalFromDatabase(ADMIN_DBNAME, principal->getName());
        principal->markDatabaseAsProbed(ADMIN_DBNAME);
        const std::string dbname = principal->getName().getDB().toString();
        _acquirePrivilegesForPrincipalFromDatabase(dbname, principal->getName());
        principal->markDatabaseAsProbed(dbname);
    }