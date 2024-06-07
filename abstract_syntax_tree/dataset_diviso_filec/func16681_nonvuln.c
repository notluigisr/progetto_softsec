    virtual Status checkAuthForCommand(Client* client,
                                       const std::string& dbname,
                                       const BSONObj& cmdObj) const {
        return auth::checkAuthForRolesInfoCommand(client, dbname, cmdObj);
    }