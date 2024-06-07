Value ExpressionStrLenBytes::evaluate(const Document& root) const {
    Value str(vpOperand[0]->evaluate(root));

    uassert(34473,
            str::stream() << "STR"
                          << typeName(str.getType()),
            str.getType() == String);

    size_t strLen = str.getString().size();

    uassert(34470,
            "STR",
            strLen <= std::numeric_limits<int>::max());
    return Value(static_cast<int>(strLen));
}