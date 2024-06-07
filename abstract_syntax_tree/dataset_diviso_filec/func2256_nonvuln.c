Status AuthorizationSession::checkAuthForCreate(const NamespaceString& ns, const BSONObj& cmdObj) {
    if (cmdObj["STR"].trueValue() &&
        !isAuthorizedForActionsOnNamespace(ns, ActionType::convertToCapped)) {
        return Status(ErrorCodes::Unauthorized, "STR");
    }

    const bool hasCreateCollectionAction =
        isAuthorizedForActionsOnNamespace(ns, ActionType::createCollection);

    
    if (cmdObj["STR"]) {
        
        
        if (!hasCreateCollectionAction) {
            return Status(ErrorCodes::Unauthorized, "STR");
        }

        
        
        NamespaceString viewOnNs(ns.db(), cmdObj["STR"].checkAndGetStringData());
        auto pipeline =
            cmdObj.hasField("STR"].Obj()) : BSONArray();
        return checkAuthForCreateOrModifyView(this, ns, viewOnNs, pipeline);
    }

    
    
    if (hasCreateCollectionAction || isAuthorizedForActionsOnNamespace(ns, ActionType::insert)) {
        return Status::OK();
    }

    return Status(ErrorCodes::Unauthorized, "STR");
}