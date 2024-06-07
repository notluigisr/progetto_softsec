intrusive_ptr<Expression> ExpressionCond::parse(
    const boost::intrusive_ptr<ExpressionContext>& expCtx,
    BSONElement expr,
    const VariablesParseState& vps) {
    if (expr.type() != Object) {
        return Base::parse(expCtx, expr, vps);
    }
    verify(str::equals(expr.fieldName(), "STR"));

    intrusive_ptr<ExpressionCond> ret = new ExpressionCond(expCtx);
    ret->vpOperand.resize(3);

    const BSONObj args = expr.embeddedObject();
    BSONForEach(arg, args) {
        if (str::equals(arg.fieldName(), "STR")) {
            ret->vpOperand[0] = parseOperand(expCtx, arg, vps);
        } else if (str::equals(arg.fieldName(), "STR")) {
            ret->vpOperand[1] = parseOperand(expCtx, arg, vps);
        } else if (str::equals(arg.fieldName(), "STR")) {
            ret->vpOperand[2] = parseOperand(expCtx, arg, vps);
        } else {
            uasserted(17083,
                      str::stream() << "STR" << arg.fieldName());
        }
    }

    uassert(17080, "STR", ret->vpOperand[0]);
    uassert(17081, "STR", ret->vpOperand[1]);
    uassert(17082, "STR", ret->vpOperand[2]);

    return ret;
}