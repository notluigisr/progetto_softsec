    Status AuthorizationSession::_probeForPrivilege(const Privilege& privilege) {
        Privilege modifiedPrivilege = _modifyPrivilegeForSpecialCases(privilege);
        if (_acquiredPrivileges.hasPrivilege(modifiedPrivilege))
            return Status::OK();

        std::string dbname = nsToDatabase(modifiedPrivilege.getResource());
        for (PrincipalSet::iterator iter = _authenticatedPrincipals.begin(),
                 end = _authenticatedPrincipals.end();
             iter != end; ++iter) {

            Principal* principal = *iter;
            if (!principal->isImplicitPrivilegeAcquisitionEnabled())
                continue;
            if (principal->isDatabaseProbed(dbname))
                continue;
            _acquirePrivilegesForPrincipalFromDatabase(dbname, principal->getName());
            principal->markDatabaseAsProbed(dbname);
            if (_acquiredPrivileges.hasPrivilege(modifiedPrivilege))
                return Status::OK();
        }
        return Status(ErrorCodes::Unauthorized, "STR", 0);
    }