zsetdevice(i_ctx_t *i_ctx_p)
{
    gx_device *dev = gs_currentdevice(igs);
    os_ptr op = osp;
    int code = 0;

    check_write_type(*op, t_device);
    if (dev->LockSafetyParams) {	  
        if(op->value.pdevice != dev) 	  
            return_error(gs_error_invalidaccess);
    }
    dev->ShowpageCount = 0;

    if (op->value.pdevice == 0)
        return gs_note_error(gs_error_undefined);

    code = gs_setdevice_no_erase(igs, op->value.pdevice);
    if (code < 0)
        return code;

    make_bool(op, code != 0);	
    invalidate_stack_devices(i_ctx_p);
    clear_pagedevice(istate);
    return code;
}