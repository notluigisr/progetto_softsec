EXPORTED void annotatemore_close(void)
{
    
    while (all_dbs_head)
        annotate_closedb(all_dbs_head);

    annotatemore_dbopen = 0;
}