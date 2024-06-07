z2restore(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    check_type(*op, t_save);

    while (gs_gstate_saved(gs_gstate_saved(igs))) {
        if (restore_page_device(igs, gs_gstate_saved(igs)))
            return push_callout(i_ctx_p, "STR");
        gs_grestore(igs);
    }
    if (restore_page_device(igs, gs_gstate_saved(igs)))
        return push_callout(i_ctx_p, "STR");
    return zrestore(i_ctx_p);
}