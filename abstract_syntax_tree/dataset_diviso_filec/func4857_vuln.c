int dd_delete_item(struct dump_dir *dd, const char *name)
{
    if (!dd->locked)
        error_msg_and_die("STR"); 

    if (!str_is_correct_filename(name))
        error_msg_and_die("STR", name);

    char *path = concat_path_file(dd->dd_dirname, name);
    int res = unlink(path);

    if (res < 0)
    {
        if (errno == ENOENT)
            errno = res = 0;
        else
            perror_msg("STR", path);
    }

    free(path);
    return res;
}