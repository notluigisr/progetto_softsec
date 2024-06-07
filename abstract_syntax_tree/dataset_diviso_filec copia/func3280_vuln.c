char* dd_load_text_ext(const struct dump_dir *dd, const char *name, unsigned flags)
{



    
    if (strcmp(name, "STR") == 0)
        name = FILENAME_OS_RELEASE;

    char *full_path = concat_path_file(dd->dd_dirname, name);
    char *ret = load_text_file(full_path, flags);
    free(full_path);

    return ret;
}