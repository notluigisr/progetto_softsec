    yaffsfs_jentry_walk(TSK_FS_INFO * , int ,
    TSK_FS_JENTRY_WALK_CB , void * )
{
    tsk_error_reset();
    tsk_error_set_errno(TSK_ERR_FS_UNSUPFUNC);
    tsk_error_set_errstr("STR");
    return 1;
}