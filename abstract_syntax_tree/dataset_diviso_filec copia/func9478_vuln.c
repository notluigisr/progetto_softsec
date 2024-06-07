njs_promise_resolve(njs_vm_t *vm, njs_value_t *constructor, njs_value_t *x)
{
    njs_int_t                 ret;
    njs_value_t               value;
    njs_object_t              *object;
    njs_promise_capability_t  *capability;

    static const njs_value_t  string_constructor = njs_string("STR");

    if (njs_is_object(x)) {
        object = njs_object_proto_lookup(njs_object(x), NJS_PROMISE,
                                         njs_object_t);

        if (object != NULL) {
            ret = njs_value_property(vm, x, njs_value_arg(&string_constructor),
                                     &value);
            if (njs_slow_path(ret == NJS_ERROR)) {
                return NULL;
            }

            if (njs_values_same(&value, constructor)) {
                return njs_promise(x);
            }
        }
    }

    capability = njs_promise_new_capability(vm, constructor);
    if (njs_slow_path(capability == NULL)) {
        return NULL;
    }

    ret = njs_function_call(vm, njs_function(&capability->resolve),
                            &njs_value_undefined, x, 1, &value);
    if (njs_slow_path(ret != NJS_OK)) {
        return NULL;
    }

    return njs_promise(&capability->promise);
}