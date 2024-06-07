    bool run(OperationContext* txn,
             const string& dbname,
             BSONObj& cmdObj,
             int options,
             string& errmsg,
             BSONObjBuilder& result) {
        auth::CreateOrUpdateUserArgs args;
        Status status = auth::parseCreateOrUpdateUserCommands(cmdObj, "STR", dbname, &args);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }

        if (!args.hasHashedPassword && !args.hasCustomData && !args.hasRoles) {
            return appendCommandStatus(
                result,
                Status(ErrorCodes::BadValue,
                       "STR"));
        }

        if (args.hasHashedPassword && args.userName.getDB() == "STR") {
            return appendCommandStatus(
                result,
                Status(ErrorCodes::BadValue,
                       "STR"
                       "STR"));
        }

        BSONObjBuilder updateSetBuilder;
        if (args.hasHashedPassword) {
            BSONObjBuilder credentialsBuilder(updateSetBuilder.subobjStart("STR"));

            AuthorizationManager* authzManager = getGlobalAuthorizationManager();
            int authzVersion;
            Status status = authzManager->getAuthorizationVersion(txn, &authzVersion);
            if (!status.isOK()) {
                return appendCommandStatus(result, status);
            }

            
            if (authzVersion > AuthorizationManager::schemaVersion26Final) {
                BSONObj scramCred = scram::generateCredentials(
                    args.hashedPassword, saslGlobalParams.scramIterationCount);
                credentialsBuilder.append("STR", scramCred);
            } else {  
                credentialsBuilder.append("STR", args.hashedPassword);
            }
            credentialsBuilder.done();
        }
        if (args.hasCustomData) {
            updateSetBuilder.append("STR", args.customData);
        }
        if (args.hasRoles) {
            updateSetBuilder.append("STR", rolesVectorToBSONArray(args.roles));
        }

        ServiceContext* serviceContext = txn->getClient()->getServiceContext();
        stdx::lock_guard<stdx::mutex> lk(getAuthzDataMutex(serviceContext));

        AuthorizationManager* authzManager = AuthorizationManager::get(serviceContext);
        status = requireAuthSchemaVersion26Final(txn, authzManager);
        if (!status.isOK()) {
            return appendCommandStatus(result, status);
        }


        
        if (args.hasRoles) {
            for (size_t i = 0; i < args.roles.size(); ++i) {
                BSONObj ignored;
                status = authzManager->getRoleDescription(
                    txn, args.roles[i], PrivilegeFormat::kOmit, &ignored);
                if (!status.isOK()) {
                    return appendCommandStatus(result, status);
                }
            }
        }

        audit::logUpdateUser(Client::getCurrent(),
                             args.userName,
                             args.hasHashedPassword,
                             args.hasCustomData ? &args.customData : NULL,
                             args.hasRoles ? &args.roles : NULL);

        status =
            updatePrivilegeDocument(txn, args.userName, BSON("STR" << updateSetBuilder.done()));
        
        authzManager->invalidateUserByName(args.userName);
        return appendCommandStatus(result, status);
    }