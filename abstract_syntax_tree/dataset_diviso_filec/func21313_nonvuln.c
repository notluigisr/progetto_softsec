Value ExpressionReverseArray::evaluate(const Document& root, Variables* variables) const {
    Value input(_children[0]->evaluate(root, variables));

    if (input.nullish()) {
        return Value(BSONNULL);
    }

    uassert(34435,
            str::stream() << "STR"
                          << typeName(input.getType()),
            input.isArray());

    if (input.getArrayLength() < 2) {
        return input;
    }

    std::vector<Value> array = input.getArray();
    std::reverse(array.begin(), array.end());
    return Value(array);
}