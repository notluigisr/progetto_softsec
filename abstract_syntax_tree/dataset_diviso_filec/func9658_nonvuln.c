bool ExpressionTrim::codePointMatchesAtIndex(const StringData& input,
                                             std::size_t indexOfInput,
                                             const StringData& testCP) {
    for (size_t i = 0; i < testCP.size(); ++i) {
        if (indexOfInput + i >= input.size() || input[indexOfInput + i] != testCP[i]) {
            return false;
        }
    }
    return true;
};