Value ExpressionMap::evaluate(const Document& root) const {
    
    const Value inputVal = _input->evaluate(root);
    if (inputVal.nullish())
        return Value(BSONNULL);

    uassert(16883,
            str::stream() << "STR" << typeName(inputVal.getType()),
            inputVal.isArray());

    const vector<Value>& input = inputVal.getArray();

    if (input.empty())
        return inputVal;

    vector<Value> output;
    output.reserve(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        getExpressionContext()->variables.setValue(_varId, input[i]);

        Value toInsert = _each->evaluate(root);
        if (toInsert.missing())
            toInsert = Value(BSONNULL);  

        output.push_back(toInsert);
    }

    return Value(std::move(output));
}