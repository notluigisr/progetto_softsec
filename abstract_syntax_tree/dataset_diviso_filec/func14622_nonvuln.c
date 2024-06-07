Value ExpressionZip::serialize(bool explain) const {
    vector<Value> serializedInput;
    vector<Value> serializedDefaults;
    Value serializedUseLongestLength = Value(_useLongestLength);

    for (auto&& expr : _inputs) {
        serializedInput.push_back(expr.get()->serialize(explain));
    }

    for (auto&& expr : _defaults) {
        serializedDefaults.push_back(expr.get()->serialize(explain));
    }

    return Value(DOC("STR"
                                            << Value(serializedDefaults) << "STR"
                                            << serializedUseLongestLength)));
}