Status AuthorizationManagerImpl::getRoleDescriptionsForDB(
    OperationContext* opCtx,
    StringData dbname,
    PrivilegeFormat privileges,
    AuthenticationRestrictionsFormat restrictions,
    bool showBuiltinRoles,
    vector<BSONObj>* result) {
    auto lk = _externalState->lock(opCtx);
    return _externalState->getRoleDescriptionsForDB(
        opCtx, dbname, privileges, restrictions, showBuiltinRoles, result);
}