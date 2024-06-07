Value DocumentSourceGroup::computeId(const Document& root) {
    
    if (_idExpressions.size() == 1) {
        Value retValue = _idExpressions[0]->evaluate(root, &pExpCtx->variables);
        return retValue.missing() ? Value(BSONNULL) : std::move(retValue);
    }

    
    vector<Value> vals;
    vals.reserve(_idExpressions.size());
    for (size_t i = 0; i < _idExpressions.size(); i++) {
        vals.push_back(_idExpressions[i]->evaluate(root, &pExpCtx->variables));
    }
    return Value(std::move(vals));
}