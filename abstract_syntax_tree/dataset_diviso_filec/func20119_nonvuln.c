vim_stat(const char *name, stat_T *stp)
{
    
    
    return illegal_slash(name) ? -1 : stat(name, stp);
}