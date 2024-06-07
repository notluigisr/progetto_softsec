void addReadWriteDbPrivileges(PrivilegeVector* privileges, StringData dbName) {
    addReadOnlyDbPrivileges(privileges, dbName);
    Privilege::addPrivilegeToPrivilegeVector(
        privileges, Privilege(ResourcePattern::forDatabaseName(dbName), readWriteRoleActions));
    Privilege::addPrivilegeToPrivilegeVector(
        privileges,
        Privilege(ResourcePattern::forExactNamespace(NamespaceString(dbName, "STR")),
                  readWriteRoleActions));
}