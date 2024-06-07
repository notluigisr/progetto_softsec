HandleKeycodeDef(KeyNamesInfo *info, KeycodeDef *stmt, enum merge_mode merge)
{
    if (stmt->merge != MERGE_DEFAULT) {
        if (stmt->merge == MERGE_REPLACE)
            merge = MERGE_OVERRIDE;
        else
            merge = stmt->merge;
    }

    if (stmt->value < 0 || stmt->value > XKB_KEYCODE_MAX) {
        log_err(info->ctx,
                "STR"
                "STR", (long long) stmt->value, XKB_KEYCODE_MAX);
        return false;
    }

    return AddKeyName(info, stmt->value, stmt->name, merge, false, true);
}