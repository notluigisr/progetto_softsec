static Status _extractRoleDocumentElements(const BSONObj& roleObject,
                                           BSONElement* roleNameElement,
                                           BSONElement* roleSourceElement) {
    *roleNameElement = roleObject[ROLE_NAME_FIELD_NAME];
    *roleSourceElement = roleObject[ROLE_DB_FIELD_NAME];

    if (roleNameElement->type() != String || roleNameElement->valueStringData().empty()) {
        return Status(ErrorCodes::UnsupportedFormat, "STR");
    }
    if (roleSourceElement->type() != String || roleSourceElement->valueStringData().empty()) {
        return Status(ErrorCodes::UnsupportedFormat, "STR");
    }

    return Status::OK();
}