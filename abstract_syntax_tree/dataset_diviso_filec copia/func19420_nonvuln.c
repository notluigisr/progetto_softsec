Status checkAuthForCreateOrModifyView(AuthorizationSession* authzSession,
                                      const NamespaceString& viewNs,
                                      const NamespaceString& viewOnNs,
                                      const BSONArray& viewPipeline,
                                      bool isMongos) {
    
    if (!authzSession->isAuthorizedForActionsOnNamespace(viewNs, ActionType::find)) {
        return Status::OK();
    }

    
    
    
    auto statusWithPrivs = authzSession->getPrivilegesForAggregate(
        viewOnNs,
        BSON("STR" << BSONObj()),
        isMongos);
    PrivilegeVector privileges = uassertStatusOK(statusWithPrivs);
    if (!authzSession->isAuthorizedForPrivileges(privileges)) {
        return Status(ErrorCodes::Unauthorized, "STR");
    }
    return Status::OK();
}