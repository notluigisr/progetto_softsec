    bool run(OperationContext* opCtx,
             const string& dbname,
             const BSONObj& cmdObj,
             BSONObjBuilder& result) {

        RoleName roleName;
        PrivilegeVector privilegesToAdd;
        Status status = auth::parseAndValidateRolePrivilegeManipulationCommands(
            cmdObj, "STR", dbname, &roleName, &privilegesToAdd);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        ServiceContext* serviceContext = opCtx->getClient()->getServiceContext();
        stdx::lock_guard<stdx::mutex> lk(getAuthzDataMutex(serviceContext));

        AuthorizationManager* authzManager = AuthorizationManager::get(serviceContext);
        status = requireAuthSchemaVersion26Final(opCtx, authzManager);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        if (RoleGraph::isBuiltinRole(roleName)) {
            return appendCommandStatus(
                result,
                Status(ErrorCodes::InvalidRoleModification,
                       str::stream() << roleName.getFullName()
                                     << "STR"));
        }

        status = checkOkayToGrantPrivilegesToRole(roleName, privilegesToAdd);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        BSONObj roleDoc;
        status = authzManager->getRoleDescription(opCtx,
                                                  roleName,
                                                  PrivilegeFormat::kShowSeparate,
                                                  AuthenticationRestrictionsFormat::kOmit,
                                                  &roleDoc);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        PrivilegeVector privileges;
        status = auth::parseAndValidatePrivilegeArray(BSONArray(roleDoc["STR"].Obj()),
                                                      &privileges);

        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        for (PrivilegeVector::iterator it = privilegesToAdd.begin(); it != privilegesToAdd.end();
             ++it) {
            Privilege::addPrivilegeToPrivilegeVector(&privileges, *it);
        }

        
        mutablebson::Document updateObj;
        mutablebson::Element setElement = updateObj.makeElementObject("STR");
        status = updateObj.root().pushBack(setElement);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }
        mutablebson::Element privilegesElement = updateObj.makeElementArray("STR");
        status = setElement.pushBack(privilegesElement);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }
        status = authzManager->getBSONForPrivileges(privileges, privilegesElement);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        BSONObjBuilder updateBSONBuilder;
        updateObj.writeTo(&updateBSONBuilder);

        audit::logGrantPrivilegesToRole(Client::getCurrent(), roleName, privilegesToAdd);

        status = updateRoleDocument(opCtx, roleName, updateBSONBuilder.done());
        
        authzManager->invalidateUserCache();
        return appendCommandStatus(result, status);
    }