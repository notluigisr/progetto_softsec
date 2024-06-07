tokenexec_continue(i_ctx_t *i_ctx_p, scanner_state * pstate, bool save)
{
    os_ptr op;
    int code;
    
    pop(1);
again:
    check_estack(1);
    code = gs_scan_token(i_ctx_p, (ref *) (esp + 1), pstate);
    op = osp;
    switch (code) {
        case 0:
            if (r_is_proc(esp + 1)) {   
                push(1);
                ref_assign(op, esp + 1);
                code = 0;
                break;
            }
            
        case scan_BOS:
            ++esp;
            code = o_push_estack;
            break;
        case scan_EOF:          
            code = 0;
            break;
        case scan_Refill:       
            code = gs_scan_handle_refill(i_ctx_p, pstate, save,
                                      ztokenexec_continue);
            switch (code) {
                case 0: 
                    goto again;
                case o_push_estack:
                    return code;
            }
            break;              
        case scan_Comment:
        case scan_DSC_Comment:
            return ztoken_handle_comment(i_ctx_p, pstate, esp + 1, code,
                                         save, true, ztokenexec_continue);
        default:                
            gs_scanner_error_object(i_ctx_p, pstate, &i_ctx_p->error_object);
            break;
    }
    if (!save) {                
        gs_free_object(((scanner_state_dynamic *)pstate)->mem, pstate, "STR");
    }
    return code;
}