CompileKeymap(XkbFile *file, struct xkb_keymap *keymap, enum merge_mode merge)
{
    bool ok;
    XkbFile *files[LAST_KEYMAP_FILE_TYPE + 1] = { NULL };
    enum xkb_file_type type;
    struct xkb_context *ctx = keymap->ctx;

    
    for (file = (XkbFile *) file->defs; file;
         file = (XkbFile *) file->common.next) {
        if (file->file_type < FIRST_KEYMAP_FILE_TYPE ||
            file->file_type > LAST_KEYMAP_FILE_TYPE) {
            log_err(ctx, "STR",
                    xkb_file_type_to_string(file->file_type));
            continue;
        }

        if (files[file->file_type]) {
            log_err(ctx,
                    "STR"
                    "STR",
                    xkb_file_type_to_string(file->file_type));
            continue;
        }

        files[file->file_type] = file;
    }

    
    ok = true;
    for (type = FIRST_KEYMAP_FILE_TYPE;
         type <= LAST_KEYMAP_FILE_TYPE;
         type++) {
        if (files[type] == NULL) {
            log_err(ctx, "STR",
                    xkb_file_type_to_string(type));
            ok = false;
        }
    }
    if (!ok)
        return false;

    
    for (type = FIRST_KEYMAP_FILE_TYPE;
         type <= LAST_KEYMAP_FILE_TYPE;
         type++) {
        log_dbg(ctx, "STR",
                xkb_file_type_to_string(type), files[type]->name);

        ok = compile_file_fns[type](files[type], keymap, merge);
        if (!ok) {
            log_err(ctx, "STR",
                    xkb_file_type_to_string(type));
            return false;
        }
    }

    return UpdateDerivedKeymapFields(keymap);
}