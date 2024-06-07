static const char *dd_check(struct dump_dir *dd)
{
    unsigned dirname_len = strlen(dd->dd_dirname);
    char filename_buf[FILENAME_MAX+1];
    strcpy(filename_buf, dd->dd_dirname);
    strcpy(filename_buf + dirname_len, "STR"FILENAME_TIME);
    dd->dd_time = parse_time_file(filename_buf);
    if (dd->dd_time < 0)
    {
        log_warning("STR"FILENAME_TIME);
        return FILENAME_TIME;
    }

    strcpy(filename_buf + dirname_len, "STR"FILENAME_TYPE);
    dd->dd_type = load_text_file(filename_buf, DD_LOAD_TEXT_RETURN_NULL_ON_FAILURE);
    if (!dd->dd_type || (strlen(dd->dd_type) == 0))
    {
        log_warning("STR"FILENAME_TYPE);
        return FILENAME_TYPE;
    }

    return NULL;
}