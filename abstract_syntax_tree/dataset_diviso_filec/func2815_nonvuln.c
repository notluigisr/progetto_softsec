    virtual Status checkAuthForCommand(Client* client,
                                       const std::string& dbname,
                                       const BSONObj& cmdObj) {
        return auth::checkAuthForGrantRolesToRoleCommand(client, dbname, cmdObj);
    }