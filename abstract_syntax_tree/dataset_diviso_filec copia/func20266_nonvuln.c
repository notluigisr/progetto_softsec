static void iscsi_parse_iscsi_option(const char *target, QDict *options)
{
    QemuOptsList *list;
    QemuOpts *opts;
    const char *user, *password, *password_secret, *initiator_name,
               *header_digest, *timeout;

    list = qemu_find_opts("STR");
    if (!list) {
        return;
    }

    opts = qemu_opts_find(list, target);
    if (opts == NULL) {
        opts = QTAILQ_FIRST(&list->head);
        if (!opts) {
            return;
        }
    }

    user = qemu_opt_get(opts, "STR");
    if (user) {
        qdict_set_default_str(options, "STR", user);
    }

    password = qemu_opt_get(opts, "STR");
    if (password) {
        qdict_set_default_str(options, "STR", password);
    }

    password_secret = qemu_opt_get(opts, "STR");
    if (password_secret) {
        qdict_set_default_str(options, "STR", password_secret);
    }

    initiator_name = qemu_opt_get(opts, "STR");
    if (initiator_name) {
        qdict_set_default_str(options, "STR", initiator_name);
    }

    header_digest = qemu_opt_get(opts, "STR");
    if (header_digest) {
        
        char *qapi_value = g_ascii_strdown(header_digest, -1);
        qdict_set_default_str(options, "STR", qapi_value);
        g_free(qapi_value);
    }

    timeout = qemu_opt_get(opts, "STR");
    if (timeout) {
        qdict_set_default_str(options, "STR", timeout);
    }
}