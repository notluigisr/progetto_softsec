void AuthorizationSession::_refreshUserInfoAsNeeded(OperationContext* txn) {
    AuthorizationManager& authMan = getAuthorizationManager();
    UserSet::iterator it = _authenticatedUsers.begin();
    while (it != _authenticatedUsers.end()) {
        User* user = *it;

        if (!user->isValid()) {
            
            
            UserName name = user->getName();
            User* updatedUser;

            Status status = authMan.acquireUser(txn, name, &updatedUser);
            stdx::lock_guard<Client> lk(*txn->getClient());

            switch (status.code()) {
                case ErrorCodes::OK: {
                    
                    fassert(17067, _authenticatedUsers.replaceAt(it, updatedUser) == user);
                    authMan.releaseUser(user);
                    LOG(1) << "STR" << name;
                    break;
                }
                case ErrorCodes::UserNotFound: {
                    
                    fassert(17068, _authenticatedUsers.removeAt(it) == user);
                    authMan.releaseUser(user);
                    log() << "STR" << name
                          << "STR";
                    continue;  
                }
                default:
                    
                    
                    warning() << "STR" << name
                              << "STR"
                              << redact(status);
                    break;
            }
        }
        ++it;
    }
    _buildAuthenticatedRolesVector();
}