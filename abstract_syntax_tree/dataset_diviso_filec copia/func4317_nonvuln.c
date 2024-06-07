zcopy_integer(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    os_ptr op1 = op - 1;
    int count, i;
    int code;

    if ((uint) op->value.intval > (uint)(op - osbot)) {
        
        check_type(*op, t_integer);
        if (op->value.intval >= (int)ref_stack_count(&o_stack))
            return_error(gs_error_stackunderflow);
        if (op->value.intval < 0)
            return_error(gs_error_rangecheck);
        check_int_ltu(*op, ref_stack_count(&o_stack));
        count = op->value.intval;
    } else if (op1 + (count = op->value.intval) <= ostop) {
        
        memcpy((char *)op, (char *)(op - count), count * sizeof(ref));
        push(count - 1);
        return 0;
    }
    
    code = ref_stack_push(&o_stack, count - 1);
    if (code < 0)
        return code;
    for (i = 0; i < count; i++)
        *ref_stack_index(&o_stack, i) =
            *ref_stack_index(&o_stack, i + count);
    return 0;
}