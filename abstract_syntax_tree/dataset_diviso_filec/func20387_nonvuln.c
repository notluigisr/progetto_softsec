bool tr_variantFromFile(tr_variant* setme, tr_variant_fmt fmt, char const* filename, tr_error** error)
{
    bool ret = false;
    uint8_t* buf;
    size_t buflen;

    buf = tr_loadFile(filename, &buflen, error);

    if (buf != NULL)
    {
        if (tr_variantFromBuf(setme, fmt, buf, buflen, filename, NULL) == 0)
        {
            ret = true;
        }
        else
        {
            tr_error_set_literal(error, 0, _("STR"));
        }

        tr_free(buf);
    }

    return ret;
}