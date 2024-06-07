njs_value_to_key(njs_vm_t *vm, njs_value_t *dst, njs_value_t *value)
{
    njs_int_t    ret;
    njs_value_t  primitive;

    if (njs_slow_path(!njs_is_primitive(value))) {
        if (njs_slow_path(njs_is_object_symbol(value))) {
            
            value = njs_object_value(value);

        } else {
            ret = njs_value_to_primitive(vm, &primitive, value, 1);
            if (njs_slow_path(ret != NJS_OK)) {
                return ret;
            }

            value = &primitive;
        }
    }

    return njs_primitive_value_to_key(vm, dst, value);
}