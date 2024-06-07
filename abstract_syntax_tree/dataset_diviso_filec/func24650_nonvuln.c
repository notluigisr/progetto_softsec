Status AuthorizationManager::getRolesDescription(OperationContext* opCtx,
                                                 const std::vector<RoleName>& roleName,
                                                 PrivilegeFormat privileges,
                                                 AuthenticationRestrictionsFormat restrictions,
                                                 BSONObj* result) {
    return _externalState->getRolesDescription(opCtx, roleName, privileges, restrictions, result);
}