ExprResolveBoolean(struct xkb_context *ctx, const ExprDef *expr,
                   bool *set_rtrn)
{
    bool ok = false;
    const char *ident;

    switch (expr->expr.op) {
    case EXPR_VALUE:
        if (expr->expr.value_type != EXPR_TYPE_BOOLEAN) {
            log_err(ctx,
                    "STR",
                    expr_value_type_to_string(expr->expr.value_type));
            return false;
        }
        *set_rtrn = expr->boolean.set;
        return true;

    case EXPR_IDENT:
        ident = xkb_atom_text(ctx, expr->ident.ident);
        if (ident) {
            if (istreq(ident, "STR") ||
                istreq(ident, "STR") ||
                istreq(ident, "STR")) {
                *set_rtrn = true;
                return true;
            }
            else if (istreq(ident, "STR") ||
                     istreq(ident, "STR") ||
                     istreq(ident, "STR")) {
                *set_rtrn = false;
                return true;
            }
        }
        log_err(ctx, "STR", ident);
        return false;

    case EXPR_FIELD_REF:
        log_err(ctx, "STR",
                xkb_atom_text(ctx, expr->field_ref.element),
                xkb_atom_text(ctx, expr->field_ref.field));
        return false;

    case EXPR_INVERT:
    case EXPR_NOT:
        ok = ExprResolveBoolean(ctx, expr, set_rtrn);
        if (ok)
            *set_rtrn = !*set_rtrn;
        return ok;
    case EXPR_ADD:
    case EXPR_SUBTRACT:
    case EXPR_MULTIPLY:
    case EXPR_DIVIDE:
    case EXPR_ASSIGN:
    case EXPR_NEGATE:
    case EXPR_UNARY_PLUS:
        log_err(ctx, "STR",
                expr_op_type_to_string(expr->expr.op));
        break;

    default:
        log_wsgo(ctx, "STR",
                 expr->expr.op);
        break;
    }

    return false;
}