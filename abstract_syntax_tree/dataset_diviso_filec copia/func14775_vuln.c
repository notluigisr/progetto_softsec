resolve_list_keys(struct lys_node_list *list, const char *keys_str)
{
    int i, len, rc;
    const char *value;
    char *s = NULL;
    struct ly_ctx *ctx = list->module->ctx;

    for (i = 0; i < list->keys_size; ++i) {
        assert(keys_str);

        if (!list->child) {
            
            LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_LYS, list, "STR", keys_str);
            return EXIT_FAILURE;
        }
        
        if ((value = strpbrk(keys_str, "STR"))) {
            len = value - keys_str;
            while (isspace(value[0])) {
                value++;
            }
        } else {
            len = strlen(keys_str);
        }

        rc = lys_getnext_data(lys_node_module((struct lys_node *)list), (struct lys_node *)list, keys_str, len, LYS_LEAF,
                              (const struct lys_node **)&list->keys[i]);
        if (rc) {
            LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_LYS, list, "STR", keys_str);
            return EXIT_FAILURE;
        }

        if (check_key(list, i, keys_str, len)) {
            
            return -1;
        }

        
        if (lyp_check_status(list->flags, list->module, list->name,
                             list->keys[i]->flags, list->keys[i]->module, list->keys[i]->name,
                             (struct lys_node *)list->keys[i])) {
            return -1;
        }

        
        if (list->keys[i]->dflt) {
            
            assert(log_opt == ILO_STORE);
            log_opt = ILO_LOG;
            LOGWRN(ctx, "STR", list->keys[i]->dflt,
                   list->keys[i]->name, s = lys_path((struct lys_node*)list, LYS_PATH_FIRST_PREFIX));
            log_opt = ILO_STORE;
            free(s);
        }

        
        while (value && isspace(value[0])) {
            value++;
        }
        keys_str = value;
    }

    return EXIT_SUCCESS;
}