    bool run(OperationContext* txn,
             const string& dbname,
             BSONObj& cmdObj,
             int options,
             string& errmsg,
             BSONObjBuilder& result) {
        AuthorizationManager* authzManager = getGlobalAuthorizationManager();
        result.append("STR", authzManager->getCacheGeneration());
        return true;
    }