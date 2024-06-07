zsetdevice(i_ctx_t *i_ctx_p)
{
    gx_device *odev = NULL, *dev = gs_currentdevice(igs);
    os_ptr op = osp;
    int code = dev_proc(dev, dev_spec_op)(dev,
                        gxdso_current_output_device, (void *)&odev, 0);

    if (code < 0)
        return code;

    check_write_type(*op, t_device);
    if (odev->LockSafetyParams) {	  
        if(op->value.pdevice != odev) 	  
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