Status AuthorizationManagerImpl::_fetchUserV2(OperationContext* opCtx,
                                              const UserName& userName,
                                              std::unique_ptr<User>* acquiredUser) {
    BSONObj userObj;
    Status status = getUserDescription(opCtx, userName, &userObj);
    if (!status.isOK()) {
        return status;
    }

    
    
    auto user = stdx::make_unique<User>(userName);

    status = _initializeUserFromPrivilegeDocument(user.get(), userObj);
    if (!status.isOK()) {
        return status;
    }
    acquiredUser->reset(user.release());
    return Status::OK();
}