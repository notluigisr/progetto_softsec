    bool run(OperationContext* opCtx,
             const string& dbname,
             const BSONObj& cmdObj,
             BSONObjBuilder& result) {
        Status status = auth::parseAndValidateDropAllUsersFromDatabaseCommand(cmdObj, dbname);
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

        audit::logDropAllUsersFromDatabase(Client::getCurrent(), dbname);

        long long numRemoved;
        status = removePrivilegeDocuments(
            opCtx, BSON(AuthorizationManager::USER_DB_FIELD_NAME << dbname), &numRemoved);
        
        authzManager->invalidateUsersFromDB(dbname);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        result.append("STR", numRemoved);
        return true;
    }