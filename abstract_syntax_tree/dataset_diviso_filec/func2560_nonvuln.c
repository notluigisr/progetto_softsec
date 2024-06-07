Value ExpressionIfNull::evaluate(const Document& root, Variables* variables) const {
    Value pLeft(_children[0]->evaluate(root, variables));
    if (!pLeft.nullish())
        return pLeft;

    Value pRight(_children[1]->evaluate(root, variables));
    return pRight;
}