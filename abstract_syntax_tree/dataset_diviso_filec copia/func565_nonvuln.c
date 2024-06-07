njs_type_string(njs_value_type_t type)
{
    switch (type) {
    case NJS_NULL:
        return "STR";

    case NJS_UNDEFINED:
        return "STR";

    case NJS_BOOLEAN:
        return "STR";

    case NJS_NUMBER:
        return "STR";

    case NJS_SYMBOL:
        return "STR";

    case NJS_STRING:
        return "STR";

    case NJS_INVALID:
        return "STR";

    case NJS_OBJECT:
    case NJS_OBJECT_VALUE:
        return "STR";

    case NJS_ARRAY:
        return "STR";

    case NJS_ARRAY_BUFFER:
        return "STR";

    case NJS_TYPED_ARRAY:
        return "STR";

    case NJS_FUNCTION:
        return "STR";

    case NJS_REGEXP:
        return "STR";

    case NJS_DATE:
        return "STR";

    case NJS_PROMISE:
        return "STR";

    default:
        return NULL;
    }
}