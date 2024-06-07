Status V2UserDocumentParser::checkValidRoleObject(const BSONObj& roleObject) {
    BSONElement roleNameElement;
    BSONElement roleSourceElement;
    return _extractRoleDocumentElements(roleObject, &roleNameElement, &roleSourceElement);
}