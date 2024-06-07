file_continue(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    es_ptr pscratch = esp - 2;
    file_enum *pfen = r_ptr(esp - 1, file_enum);
    int devlen = esp[-3].value.intval;
    gx_io_device *iodev = r_ptr(esp - 4, gx_io_device);
    uint len = r_size(pscratch);
    uint code;

    if (len < devlen)
        return_error(gs_error_rangecheck);     
    memcpy((char *)pscratch->value.bytes, iodev->dname, devlen);
    code = iodev->procs.enumerate_next(pfen, (char *)pscratch->value.bytes + devlen,
                len - devlen);
    if (code == ~(uint) 0) {    
        esp -= 5;               
        return o_pop_estack;
    } else if (code > len)      
        return_error(gs_error_rangecheck);
    else {
        push(1);
        ref_assign(op, pscratch);
        r_set_size(op, code + devlen);
        push_op_estack(file_continue);  
        *++esp = pscratch[2];   
        return o_push_estack;
    }
}