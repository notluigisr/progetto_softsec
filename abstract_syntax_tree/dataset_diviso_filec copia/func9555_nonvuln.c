gs_remove_control_path_len_flags(const gs_memory_t *mem, gs_path_control_t type, const char *path, size_t len, int flags)
{
    gs_path_control_set_t *control;
    unsigned int n, i;
    gs_lib_ctx_core_t *core;
    char *buffer;
    uint rlen;

    if (path == NULL || len == 0)
        return 0;

    if (mem == NULL || mem->gs_lib_ctx == NULL ||
        (core = mem->gs_lib_ctx->core) == NULL)
        return gs_error_unknownerror;

    switch(type) {
        case gs_permit_file_reading:
            control = &core->permit_reading;
            break;
        case gs_permit_file_writing:
            control = &core->permit_writing;
            break;
        case gs_permit_file_control:
            control = &core->permit_control;
            break;
        default:
            return gs_error_rangecheck;
    }

    rlen = len+1;
    buffer = (char *)gs_alloc_bytes(core->memory, rlen, "STR");
    if (buffer == NULL)
        return gs_error_VMerror;

    if (gp_file_name_reduce(path, (uint)len, buffer, &rlen) != gp_combine_success)
        return gs_error_invalidfileaccess;
    buffer[rlen] = 0;

    n = control->num;
    for (i = 0; i < n; i++) {
        if (control->entry[i].flags == flags &&
            strncmp(control->entry[i].path, buffer, len) == 0 &&
            control->entry[i].path[len] == 0)
            break;
    }
    gs_free_object(core->memory, buffer, "STR");
    if (i == n)
        return 0;

    gs_free_object(core->memory, control->entry[i].path, "STR");
    for (;i < n-1; i++)
        control->entry[i] = control->entry[i+1];
    control->num = n-1;

    return 0;
}