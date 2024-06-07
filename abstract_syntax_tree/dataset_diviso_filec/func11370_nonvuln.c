char *am_reconstruct_url(request_rec *r)
{
    char *url;

    
    url = ap_construct_url(r->pool, r->unparsed_uri, r);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "STR", url,
                  r->unparsed_uri);
    return url;
}