zeqproc(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref2_t stack[MAX_DEPTH + 1];
    ref2_t *top = stack;

    make_array(&stack[0].proc1, 0, 1, op - 1);
    make_array(&stack[0].proc2, 0, 1, op);
    for (;;) {
        long i;

        if (r_size(&top->proc1) == 0) {
            
            if (top == stack) {
                
                make_true(op - 1);
                pop(1);
                return 0;
            }
            --top;
            continue;
        }
        
        i = r_size(&top->proc1) - 1;
        array_get(imemory, &top->proc1, i, &top[1].proc1);
        array_get(imemory, &top->proc2, i, &top[1].proc2);
        r_dec_size(&top->proc1, 1);
        ++top;
        
#if 0
        if (r_has_attr(&top->proc1, a_executable) !=
            r_has_attr(&top->proc2, a_executable)
            )
            break;
#endif
        if (obj_eq(imemory, &top->proc1, &top->proc2)) {
            
            if (r_type(&top->proc1) != r_type(&top->proc2) &&
                (r_type(&top->proc1) == t_name ||
                 r_type(&top->proc2) == t_name)
                )
                break;
            --top;		
            continue;
        }
        if (r_is_array(&top->proc1) && r_is_array(&top->proc2) &&
            r_size(&top->proc1) == r_size(&top->proc2) &&
            top < stack + (MAX_DEPTH - 1)
            ) {
            
            continue;
        }
        break;
    }
    
    make_false(op - 1);
    pop(1);
    return 0;
}