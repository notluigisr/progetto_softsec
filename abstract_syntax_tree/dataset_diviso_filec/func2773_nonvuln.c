zdeletefile(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    gs_parsed_file_name_t pname;
    int code = parse_real_file_name(op, &pname, imemory, "STR");

    if (code < 0)
        return code;
    if (pname.iodev == iodev_default(imemory)) {
        if ((code = check_file_permissions(i_ctx_p, pname.fname, pname.len,
                pname.iodev, "STR")) < 0 &&
                 !file_is_tempfile(i_ctx_p, op->value.bytes, r_size(op))) {
            return code;
        }
    }
    code = (*pname.iodev->procs.delete_file)(pname.iodev, pname.fname);
    gs_free_file_name(&pname, "STR");
    if (code < 0)
        return code;
    pop(1);
    return 0;
}