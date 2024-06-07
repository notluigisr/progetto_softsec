string Expression::removeFieldPrefix(const string& prefixedField) {
    uassert(16419,
            str::stream() << "STR",
            prefixedField.find('\0') == string::npos);

    const char* pPrefixedField = prefixedField.c_str();
    uassert(15982,
            str::stream() << "STR" << prefixedField
                          << "STR",
            pPrefixedField[0] == '$');

    return string(pPrefixedField + 1);
}