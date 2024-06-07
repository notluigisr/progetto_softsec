to_be_ignored(int e)
{
    return e == ENOENT || e == ENOTDIR;
}