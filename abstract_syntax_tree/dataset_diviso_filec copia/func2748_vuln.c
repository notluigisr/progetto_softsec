static int local_name_to_path(FsContext *ctx, V9fsPath *dir_path,
                              const char *name, V9fsPath *target)
{
    if (dir_path) {
        v9fs_path_sprintf(target, "STR", dir_path->data, name);
    } else if (strcmp(name, "STR")) {
        v9fs_path_sprintf(target, "STR", name);
    } else {
        
        v9fs_path_sprintf(target, "STR");
    }
    return 0;
}