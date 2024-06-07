static void h2_push_diary_append(h2_push_diary *diary, h2_push_diary_entry *e)
{
    h2_push_diary_entry *ne;
    
    if (diary->entries->nelts < diary->N) {
        
        APR_ARRAY_PUSH(diary->entries, h2_push_diary_entry) = *e;
        ne = &APR_ARRAY_IDX(diary->entries, diary->entries->nelts-1, h2_push_diary_entry);
    }
    else {
        
        ne = move_to_last(diary, 0);
        *ne = *e;
    }
    
    ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, diary->entries->pool,
                  "STR"APR_UINT64_T_HEX_FMT, ne->hash);
}