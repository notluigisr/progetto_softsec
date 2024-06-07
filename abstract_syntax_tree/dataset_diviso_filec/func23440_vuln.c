    bool run(OperationContext* opCtx,
             const string& dbname,
             const BSONObj& cmdObj,
             BSONObjBuilder& result) {
        auth::CreateOrUpdateUserArgs args;
        Status status = auth::parseCreateOrUpdateUserCommands(cmdObj, "STR", dbname, &args);
        uassertStatusOK(status);

        if (args.userName.getDB() == "STR") {
            uasserted(ErrorCodes::BadValue, "STR");
        }

        if (!args.hasPassword && args.userName.getDB() != "STR") {
            uasserted(ErrorCodes::BadValue,
                      "STR"
                      "STR");
        }

        if ((args.hasPassword) && args.userName.getDB() == "STR") {
            uasserted(ErrorCodes::BadValue,
                      "STR"
                      "STR");
        }

        if (!args.hasRoles) {
            uasserted(ErrorCodes::BadValue, "STR");
        }

#ifdef MONGO_CONFIG_SSL
        if (args.userName.getDB() == "STR" && getSSLManager() &&
            getSSLManager()->getSSLConfiguration().isClusterMember(args.userName.getUser())) {
            uasserted(ErrorCodes::BadValue,
                      "STR"
                      "STR"
                      "STR");
        }
#endif

        BSONObjBuilder userObjBuilder;
        userObjBuilder.append(
            "STR" << args.userName.getUser());
        userObjBuilder.append(AuthorizationManager::USER_NAME_FIELD_NAME, args.userName.getUser());
        userObjBuilder.append(AuthorizationManager::USER_DB_FIELD_NAME, args.userName.getDB());

        ServiceContext* serviceContext = opCtx->getClient()->getServiceContext();
        AuthorizationManager* authzManager = AuthorizationManager::get(serviceContext);

        auto lk = uassertStatusOK(requireWritableAuthSchema28SCRAM(opCtx, authzManager));

        int authzVersion;
        status = authzManager->getAuthorizationVersion(opCtx, &authzVersion);
        uassertStatusOK(status);

        BSONObjBuilder credentialsBuilder(userObjBuilder.subobjStart("STR"));
        status = buildCredentials(&credentialsBuilder, args);
        uassertStatusOK(status);
        credentialsBuilder.done();

        if (args.authenticationRestrictions && !args.authenticationRestrictions->isEmpty()) {
            credentialsBuilder.append("STR",
                                      *args.authenticationRestrictions);
        }

        if (args.hasCustomData) {
            userObjBuilder.append("STR", args.customData);
        }

        userObjBuilder.append("STR", rolesVectorToBSONArray(args.roles));

        BSONObj userObj = userObjBuilder.obj();
        V2UserDocumentParser parser;
        status = parser.checkValidUserDocument(userObj);
        uassertStatusOK(status);

        
        for (size_t i = 0; i < args.roles.size(); ++i) {
            BSONObj ignored;
            status = authzManager->getRoleDescription(opCtx, args.roles[i], &ignored);
            uassertStatusOK(status);
        }

        audit::logCreateUser(Client::getCurrent(),
                             args.userName,
                             args.hasPassword,
                             args.hasCustomData ? &args.customData : NULL,
                             args.roles,
                             args.authenticationRestrictions);
        status = insertPrivilegeDocument(opCtx, userObj);
        authzManager->invalidateUserByName(opCtx, args.userName);
        uassertStatusOK(status);
        return true;
    }