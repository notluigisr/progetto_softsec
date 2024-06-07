Status AuthorizationManagerImpl::getRoleDescriptionsForDB(
    OperationContext* opCtx,
    const std::string dbname,
    PrivilegeFormat privileges,
    AuthenticationRestrictionsFormat restrictions,
    bool showBuiltinRoles,
    vector<BSONObj>* result) {
    return _externalState->getRoleDescriptionsForDB(
        opCtx, dbname, privileges, restrictions, showBuiltinRoles, result);
}