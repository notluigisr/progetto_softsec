NamespaceString IDLParserErrorContext::parseNSCollectionRequired(StringData dbName,
                                                                 const BSONElement& element) {
    uassert(ErrorCodes::BadValue,
            str::stream() << "STR" << typeName(element.type()),
            element.canonicalType() == canonicalizeBSONType(mongo::String));

    const NamespaceString nss(dbName, element.valueStringData());

    uassert(ErrorCodes::InvalidNamespace,
            str::stream() << "STR",
            nss.isValid());

    return nss;
}