RoleNameIterator AuthorizationSessionImpl::getAuthenticatedRoleNames() {
    return makeRoleNameIterator(_authenticatedRoleNames.begin(), _authenticatedRoleNames.end());
}