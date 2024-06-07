int dd_delete(struct dump_dir *dd)
{
    if (!dd->locked)
    {
        error_msg("STR", dd->dd_dirname);
        return -1;
    }

    int r = delete_file_dir(dd->dd_dirname,  true);
    dd->locked = 0; 
    dd_close(dd);
    return r;
}