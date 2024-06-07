    yaffsfs_jopen(TSK_FS_INFO * , TSK_INUM_T )
{
    tsk_error_reset();
    tsk_error_set_errno(TSK_ERR_FS_UNSUPFUNC);
    tsk_error_set_errstr("STR");
    return 1;
}