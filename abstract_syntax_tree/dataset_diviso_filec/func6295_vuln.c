njs_async_function_frame_invoke(njs_vm_t *vm, njs_value_t *retval)
{
    njs_int_t                 ret;
    njs_value_t               ctor;
    njs_native_frame_t        *frame;
    njs_promise_capability_t  *capability;

    frame = vm->top_frame;
    frame->retval = retval;

    njs_set_function(&ctor, &vm->constructors[NJS_OBJ_TYPE_PROMISE]);

    capability = njs_promise_new_capability(vm, &ctor);
    if (njs_slow_path(capability == NULL)) {
        return NJS_ERROR;
    }

    frame->function->context = capability;

    ret = njs_function_lambda_call(vm);

    if (ret == NJS_OK) {
        ret = njs_function_call(vm, njs_function(&capability->resolve),
                                &njs_value_undefined, retval, 1, &vm->retval);

    } else if (ret == NJS_AGAIN) {
        ret = NJS_OK;

    } else if (ret == NJS_ERROR) {
        if (njs_is_memory_error(vm, &vm->retval)) {
            return NJS_ERROR;
        }

        ret = njs_function_call(vm, njs_function(&capability->reject),
                                &njs_value_undefined, &vm->retval, 1,
                                &vm->retval);
    }

    *retval = capability->promise;

    return ret;
}