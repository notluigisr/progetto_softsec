Status AuthorizationManager::getBSONForRole(RoleGraph* graph,
                                            const RoleName& roleName,
                                            mutablebson::Element result) {
    if (!graph->roleExists(roleName)) {
        return Status(ErrorCodes::RoleNotFound,
                      mongoutils::str::stream() << roleName.getFullName()
                                                << "STR");
    }
    std::string id = mongoutils::str::stream() << roleName.getDB() << "STR" << roleName.getRole();
    result.appendString("STR", id).transitional_ignore();
    result.appendString(ROLE_NAME_FIELD_NAME, roleName.getRole()).transitional_ignore();
    result.appendString(ROLE_DB_FIELD_NAME, roleName.getDB()).transitional_ignore();

    
    mutablebson::Element privilegesArrayElement =
        result.getDocument().makeElementArray("STR");
    result.pushBack(privilegesArrayElement).transitional_ignore();
    const PrivilegeVector& privileges = graph->getDirectPrivileges(roleName);
    Status status = getBSONForPrivileges(privileges, privilegesArrayElement);
    if (!status.isOK()) {
        return status;
    }

    
    mutablebson::Element rolesArrayElement = result.getDocument().makeElementArray("STR");
    result.pushBack(rolesArrayElement).transitional_ignore();
    for (RoleNameIterator roles = graph->getDirectSubordinates(roleName); roles.more();
         roles.next()) {
        const RoleName& subRole = roles.get();
        mutablebson::Element roleObj = result.getDocument().makeElementObject("");
        roleObj.appendString(ROLE_NAME_FIELD_NAME, subRole.getRole()).transitional_ignore();
        roleObj.appendString(ROLE_DB_FIELD_NAME, subRole.getDB()).transitional_ignore();
        rolesArrayElement.pushBack(roleObj).transitional_ignore();
    }

    return Status::OK();
}