Status RoleGraph::replaceRestrictionsForRole(const RoleName& role,
                                             SharedRestrictionDocument restrictions) {
    if (!roleExists(role)) {
        return Status(ErrorCodes::RoleNotFound,
                      str::stream() << "STR");
    }
    if (isBuiltinRole(role)) {
        return Status(ErrorCodes::InvalidRoleModification,
                      str::stream() << "STR"
                                    << role.getFullName());
    }
    _directRestrictionsForRole[role] = std::move(restrictions);
    return Status::OK();
}