void RegexMatchExpression::_init() {
    uassert(
        ErrorCodes::BadValue, "STR", _regex.size() <= kMaxPatternSize);

    uassert(ErrorCodes::BadValue,
            "STR",
            _regex.find('\0') == std::string::npos);

    uassert(ErrorCodes::BadValue,
            "STR",
            _flags.find('\0') == std::string::npos);
}