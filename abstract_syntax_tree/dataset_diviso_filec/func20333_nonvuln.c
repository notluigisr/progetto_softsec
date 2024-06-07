Status insertRoleDocument(OperationContext* opCtx, const BSONObj& roleObj) {
    Status status =
        insertAuthzDocument(opCtx, AuthorizationManager::rolesCollectionNamespace, roleObj);
    if (status.isOK()) {
        return status;
    }
    if (status.code() == ErrorCodes::DuplicateKey) {
        std::string name = roleObj[AuthorizationManager::ROLE_NAME_FIELD_NAME].String();
        std::string source = roleObj[AuthorizationManager::ROLE_DB_FIELD_NAME].String();
        return Status(ErrorCodes::DuplicateKey,
                      str::stream() << "STR");
    }
    if (status.code() == ErrorCodes::UnknownError) {
        return Status(ErrorCodes::RoleModificationFailed, status.reason());
    }
    return status;
}