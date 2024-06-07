Status AuthorizationManager::_initializeUserFromPrivilegeDocument(User* user,
                                                                  const BSONObj& privDoc) {
    V2UserDocumentParser parser;
    std::string userName = parser.extractUserNameFromUserDocument(privDoc);
    if (userName != user->getName().getUser()) {
        return Status(ErrorCodes::BadValue,
                      mongoutils::str::stream() << "STR"
                                                << userName
                                                << "STR"
                                                << user->getName().getUser()
                                                << "STR",
                      0);
    }

    Status status = parser.initializeUserCredentialsFromUserDocument(user, privDoc);
    if (!status.isOK()) {
        return status;
    }
    status = parser.initializeUserRolesFromUserDocument(privDoc, user);
    if (!status.isOK()) {
        return status;
    }
    status = parser.initializeUserIndirectRolesFromUserDocument(privDoc, user);
    if (!status.isOK()) {
        return status;
    }
    status = parser.initializeUserPrivilegesFromUserDocument(privDoc, user);
    if (!status.isOK()) {
        return status;
    }

    return Status::OK();
}