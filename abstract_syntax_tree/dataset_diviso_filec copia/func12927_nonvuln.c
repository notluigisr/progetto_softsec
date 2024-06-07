bool tr_variantGetStr(tr_variant const* v, char const** setme, size_t* len)
{
    bool const success = tr_variantIsString(v);

    if (success)
    {
        *setme = getStr(v);
    }

    if (len != NULL)
    {
        *len = success ? v->val.s.len : 0;
    }

    return success;
}