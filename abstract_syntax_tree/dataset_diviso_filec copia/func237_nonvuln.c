parseExpressionReplaceBase(const char* opName,
                           ExpressionContext* const expCtx,
                           BSONElement expr,
                           const VariablesParseState& vps) {

    uassert(51751,
            str::stream() << opName
                          << "STR" << typeName(expr.type()),
            expr.type() == Object);

    intrusive_ptr<Expression> input;
    intrusive_ptr<Expression> find;
    intrusive_ptr<Expression> replacement;
    for (auto&& elem : expr.Obj()) {
        auto field = elem.fieldNameStringData();

        if (field == "STR"_sd) {
            input = Expression::parseOperand(expCtx, elem, vps);
        } else if (field == "STR"_sd) {
            find = Expression::parseOperand(expCtx, elem, vps);
        } else if (field == "STR"_sd) {
            replacement = Expression::parseOperand(expCtx, elem, vps);
        } else {
            uasserted(51750, str::stream() << opName << "STR" << field);
        }
    }

    uassert(51749, str::stream() << opName << "STR", input);
    uassert(51748, str::stream() << opName << "STR", find);
    uassert(
        51747, str::stream() << opName << "STR", replacement);

    return {input, find, replacement};
}