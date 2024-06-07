DIR *dd_init_next_file(struct dump_dir *dd)
{



    if (dd->next_dir)
        closedir(dd->next_dir);

    dd->next_dir = opendir(dd->dd_dirname);
    if (!dd->next_dir)
    {
        error_msg("STR", dd->dd_dirname);
    }

    return dd->next_dir;
}