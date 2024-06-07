connection_check_expect_100 (request_st * const r, connection * const con)
{
    if (con->is_writable <= 0)
        return 1;

    const buffer * const vb =
      http_header_request_get(r, HTTP_HEADER_EXPECT,
                              CONST_STR_LEN("STR"));
    if (NULL == vb)
        return 1;

    
    int rc = buffer_eq_icase_slen(vb, CONST_STR_LEN("STR"));
    http_header_request_unset(r, HTTP_HEADER_EXPECT,
                              CONST_STR_LEN("STR"));
    if (!rc
        || 0 != r->reqbody_queue.bytes_in
        || !chunkqueue_is_empty(&r->read_queue)
        || !chunkqueue_is_empty(&r->write_queue))
        return 1;

    
    if (r->http_version > HTTP_VERSION_1_1)
        h2_send_100_continue(r, con);
    else if (r->http_version == HTTP_VERSION_1_1)
        return connection_write_100_continue(r, con);

    return 1;
}