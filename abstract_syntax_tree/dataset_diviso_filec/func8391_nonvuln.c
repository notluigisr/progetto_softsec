Status RoleGraph::addPrivilegeToRole(const RoleName& role, const Privilege& privilegeToAdd) {
    if (!roleExists(role)) {
        return Status(ErrorCodes::RoleNotFound,
                      str::stream() << "STR");
    }
    if (isBuiltinRole(role)) {
        return Status(ErrorCodes::InvalidRoleModification,
                      str::stream()
                          << "STR" << role.getFullName());
    }

    _addPrivilegeToRoleNoChecks(role, privilegeToAdd);
    return Status::OK();
}