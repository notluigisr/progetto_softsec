EXPORTED int examine_request(struct transaction_t *txn, const char *uri)
{
    int ret = 0, sasl_result = 0;
    const char *query;
    const struct namespace_t *namespace;
    struct request_line_t *req_line = &txn->req_line;

    if (!uri) uri = req_line->uri;

    
    if ((ret = check_method(txn))) return ret;

    
    if (!(txn->req_uri = parse_uri(txn->meth, uri, 1, &txn->error.desc))) {
        return HTTP_BAD_REQUEST;
    }

    
    if ((ret = preauth_check_hdrs(txn))) return ret;

    
    if ((ret = check_namespace(txn))) return ret;

    
    ret = auth_check_hdrs(txn, &sasl_result);

    if (ret && ret != HTTP_UNAUTHORIZED) return ret;

    
    namespace = txn->req_tgt.namespace;
    buf_printf(&txn->buf, "STR", config_ident,
               namespace->well_known ? strrchr(namespace->well_known, '/') :
               namespace->prefix);
    proc_register(buf_cstring(&txn->buf), txn->conn->clienthost, httpd_userid,
                  txn->req_tgt.path, txn->req_line.meth);
    buf_reset(&txn->buf);

    
    if (!httpd_userid && namespace->need_auth(txn)) {
        ret = HTTP_UNAUTHORIZED;
    }

    if (ret) return client_need_auth(txn, sasl_result);

    
    construct_hash_table(&txn->req_qparams, 10, 1);
    query = URI_QUERY(txn->req_uri);
    if (query) parse_query_params(txn, query);

    
    postauth_check_hdrs(txn);

    return 0;
}