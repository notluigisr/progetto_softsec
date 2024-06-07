Status RoleGraph::removePrivilegesFromRole(const RoleName& role,
                                           const PrivilegeVector& privilegesToRemove) {
    for (PrivilegeVector::const_iterator it = privilegesToRemove.begin();
         it != privilegesToRemove.end();
         ++it) {
        Status status = removePrivilegeFromRole(role, *it);
        if (!status.isOK()) {
            return status;
        }
    }
    return Status::OK();
}