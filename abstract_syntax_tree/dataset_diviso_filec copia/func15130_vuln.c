njs_function_lambda_call(njs_vm_t *vm)
{
    uint32_t               n;
    njs_int_t              ret;
    njs_frame_t            *frame;
    njs_value_t            *args, **local, *value;
    njs_value_t            **cur_local, **cur_closures, **cur_temp;
    njs_function_t         *function;
    njs_declaration_t      *declr;
    njs_function_lambda_t  *lambda;

    frame = (njs_frame_t *) vm->top_frame;
    function = frame->native.function;

    if (function->global && !function->closure_copied) {
        ret = njs_function_capture_global_closures(vm, function);
        if (njs_slow_path(ret != NJS_OK)) {
            return NJS_ERROR;
        }
    }

    lambda = function->u.lambda;

    args = vm->top_frame->arguments;
    local = vm->top_frame->local + function->args_offset;

    

    for (n = 0; n < function->args_count; n++) {
        if (!njs_is_valid(args)) {
            njs_set_undefined(args);
        }

        *local++ = args++;
    }

    

    cur_local = vm->levels[NJS_LEVEL_LOCAL];
    cur_closures = vm->levels[NJS_LEVEL_CLOSURE];
    cur_temp = vm->levels[NJS_LEVEL_TEMP];

    

    vm->levels[NJS_LEVEL_LOCAL] = vm->top_frame->local;
    vm->levels[NJS_LEVEL_CLOSURE] = njs_function_closures(function);
    vm->levels[NJS_LEVEL_TEMP] = frame->native.temp;

    if (lambda->rest_parameters) {
        ret = njs_function_rest_parameters_init(vm, &frame->native);
        if (njs_slow_path(ret != NJS_OK)) {
            return NJS_ERROR;
        }
    }

    

    if (lambda->self != NJS_INDEX_NONE) {
        value = njs_scope_value(vm, lambda->self);

        if (!njs_is_valid(value)) {
            njs_set_function(value, function);
        }
    }

    vm->active_frame = frame;

    

    n = lambda->ndeclarations;

    while (n != 0) {
        n--;

        declr = &lambda->declarations[n];
        value = njs_scope_value(vm, declr->index);

        *value = *declr->value;

        function = njs_function_value_copy(vm, value);
        if (njs_slow_path(function == NULL)) {
            return NJS_ERROR;
        }

        ret = njs_function_capture_closure(vm, function, function->u.lambda);
        if (njs_slow_path(ret != NJS_OK)) {
            return ret;
        }
    }

    ret = njs_vmcode_interpreter(vm, lambda->start);

    
    vm->levels[NJS_LEVEL_LOCAL] = cur_local;
    vm->levels[NJS_LEVEL_CLOSURE] = cur_closures;
    vm->levels[NJS_LEVEL_TEMP] = cur_temp;

    return ret;
}