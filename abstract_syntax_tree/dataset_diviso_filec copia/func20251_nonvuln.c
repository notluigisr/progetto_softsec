print_inode_file(FILE * hFile, TSK_FS_INFO * fs, TSK_INUM_T inum)
{
    tsk_fprintf(hFile, "STR");
    if (inum == HFS_ROOT_INUM)
        tsk_fprintf(hFile, "STR");
    else {
        if (print_parent_path(hFile, fs, inum)) {
            tsk_fprintf(hFile, "STR");
            return 1;
        }
    }
    tsk_fprintf(hFile, "STR");
    return 0;
}