    static void auditCreateOrUpdateUser(const BSONObj& userObj, bool create) {
        UserName userName = extractUserNameFromBSON(userObj);
        std::vector<RoleName> roles;
        uassertStatusOK(auth::parseRoleNamesFromBSONArray(
            BSONArray(userObj["STR"].Obj()), userName.getDB(), &roles));
        BSONObj customData;
        if (userObj.hasField("STR")) {
            customData = userObj["STR"].Obj();
        }

        boost::optional<BSONArray> authenticationRestrictions;
        if (userObj.hasField("STR")) {
            auto r = getRawAuthenticationRestrictions(
                BSONArray(userObj["STR"].Obj()));
            uassertStatusOK(r);
            authenticationRestrictions = r.getValue();
        }

        const bool hasPwd = userObj["STR") ||
            userObj["STR");
        if (create) {
            audit::logCreateUser(Client::getCurrent(),
                                 userName,
                                 hasPwd,
                                 userObj.hasField("STR") ? &customData : NULL,
                                 roles,
                                 authenticationRestrictions);
        } else {
            audit::logUpdateUser(Client::getCurrent(),
                                 userName,
                                 hasPwd,
                                 userObj.hasField("STR") ? &customData : NULL,
                                 &roles,
                                 authenticationRestrictions);
        }
    }