NamespaceString Command::parseNsCollectionRequired(const string& dbname, const BSONObj& cmdObj) {
    
    
    BSONElement first = cmdObj.firstElement();
    uassert(ErrorCodes::InvalidNamespace,
            str::stream() << "STR" << typeName(first.type()),
            first.canonicalType() == canonicalizeBSONType(mongo::String));
    const NamespaceString nss(dbname, first.valueStringData());
    uassert(ErrorCodes::InvalidNamespace,
            str::stream() << "STR",
            nss.isValid());
    return nss;
}