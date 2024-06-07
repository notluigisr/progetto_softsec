static apr_off_t bucket_mem_used(apr_bucket *b)
{
    if (APR_BUCKET_IS_FILE(b)) {
        return 0;
    }
    else {
        
        return b->length;
    }
}