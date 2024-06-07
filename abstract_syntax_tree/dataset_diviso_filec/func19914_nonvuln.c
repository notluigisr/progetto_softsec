dir_check(VALUE dir)
{
    struct dir_data *dirp = dir_get(dir);
    if (!dirp->dir) dir_closed();
    return dirp;
}