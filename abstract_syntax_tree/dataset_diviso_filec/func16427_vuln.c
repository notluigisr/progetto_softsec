CopyKeyAliasesToKeymap(struct xkb_keymap *keymap, KeyNamesInfo *info)
{
    AliasInfo *alias;
    unsigned i, num_key_aliases;
    struct xkb_key_alias *key_aliases;

    
    num_key_aliases = 0;
    darray_foreach(alias, info->aliases) {
        
        if (!XkbKeyByName(keymap, alias->real, false)) {
            log_vrb(info->ctx, 5,
                    "STR",
                    KeyNameText(info->ctx, alias->alias),
                    KeyNameText(info->ctx, alias->real));
            alias->real = XKB_ATOM_NONE;
            continue;
        }

        
        if (XkbKeyByName(keymap, alias->alias, false)) {
            log_vrb(info->ctx, 5,
                    "STR"
                    "STR",
                    KeyNameText(info->ctx, alias->alias),
                    KeyNameText(info->ctx, alias->real));
            alias->real = XKB_ATOM_NONE;
            continue;
        }

        num_key_aliases++;
    }

    
    key_aliases = NULL;
    if (num_key_aliases > 0) {
        key_aliases = calloc(num_key_aliases, sizeof(*key_aliases));
        if (!key_aliases)
            return false;
    }

    i = 0;
    darray_foreach(alias, info->aliases) {
        if (alias->real != XKB_ATOM_NONE) {
            key_aliases[i].alias = alias->alias;
            key_aliases[i].real = alias->real;
            i++;
        }
    }

    keymap->num_key_aliases = num_key_aliases;
    keymap->key_aliases = key_aliases;
    return true;
}