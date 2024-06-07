void addRestorePrivileges(PrivilegeVector* privileges) {
    ActionSet actions;
    actions << ActionType::bypassDocumentValidation << ActionType::collMod
            << ActionType::convertToCapped << ActionType::createCollection
            << ActionType::createIndex << ActionType::dropCollection << ActionType::insert;

    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forAnyNormalResource(), actions));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forCollectionName("STR"), actions));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forAnyResource(), ActionType::listCollections));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forDatabaseName("STR"), actions));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forDatabaseName("STR"), actions));

    
    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forAnyNormalResource(), userAdminRoleActions));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(ResourcePattern::forExactNamespace(
                      AuthorizationManager::defaultTempUsersCollectionNamespace),
                  ActionType::find));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(ResourcePattern::forExactNamespace(
                      AuthorizationManager::defaultTempRolesCollectionNamespace),
                  ActionType::find));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(
            ResourcePattern::forExactNamespace(AuthorizationManager::usersAltCollectionNamespace),
            actions));

    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(ResourcePattern::forExactNamespace(
                      AuthorizationManager::usersBackupCollectionNamespace),
                  actions));

    actions << ActionType::find;
    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(
            ResourcePattern::forExactNamespace(AuthorizationManager::versionCollectionNamespace),
            actions));

    
    actions << ActionType::update << ActionType::remove;
    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forCollectionName("STR"), actions));

    
    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forClusterResource(), ActionType::getParameter));

    
    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(
            ResourcePattern::forExactNamespace(AuthorizationManager::rolesCollectionNamespace),
            ActionType::createIndex));

    
    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(ResourcePattern::forClusterResource(),
                  {ActionType::forceUUID, ActionType::useUUID}));
}