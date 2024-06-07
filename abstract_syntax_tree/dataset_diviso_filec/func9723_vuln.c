njs_promise_prototype_then(njs_vm_t *vm, njs_value_t *args, njs_uint_t nargs,
    njs_index_t unused)
{
    njs_int_t                 ret;
    njs_value_t               *promise, *fulfilled, *rejected, constructor;
    njs_object_t              *object;
    njs_function_t            *function;
    njs_promise_capability_t  *capability;

    promise = njs_argument(args, 0);

    if (njs_slow_path(!njs_is_object(promise))) {
        goto failed;
    }

    object = njs_object_proto_lookup(njs_object(promise), NJS_PROMISE,
                                     njs_object_t);
    if (njs_slow_path(object == NULL)) {
        goto failed;
    }

    function = njs_promise_create_function(vm, sizeof(njs_promise_context_t));
    function->u.native = njs_promise_constructor;

    njs_set_function(&constructor, function);

    ret = njs_value_species_constructor(vm, promise, &constructor,
                                        &constructor);
    if (njs_slow_path(ret != NJS_OK)) {
        return ret;
    }

    capability = njs_promise_new_capability(vm, &constructor);
    if (njs_slow_path(capability == NULL)) {
        return NJS_ERROR;
    }

    fulfilled = njs_arg(args, nargs, 1);
    rejected = njs_arg(args, nargs, 2);

    return njs_promise_perform_then(vm, promise, fulfilled, rejected,
                                    capability);

failed:

    njs_type_error(vm, "STR");

    return NJS_ERROR;
}