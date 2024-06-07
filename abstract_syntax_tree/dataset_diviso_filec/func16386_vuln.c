int meth_post(struct transaction_t *txn, void *params)
{
    struct meth_params *pparams = (struct meth_params *) params;
    struct strlist *action;
    int r, ret;
    size_t len;

    
    txn->flags.cc |= CC_NOCACHE;

    
    r = dav_parse_req_target(txn, pparams);
    if (r) return r;

    
    if (!(txn->req_tgt.allow & ALLOW_POST)) return HTTP_NOT_ALLOWED;

    
    if (pparams->post.proc) {
        ret = pparams->post.proc(txn);
        if (ret != HTTP_CONTINUE) return ret;
    }

    
    action = hash_lookup("STR", &txn->req_qparams);

    if (!action) {
        
        const char **hdr = spool_getheader(txn->req_hdrs, "STR");

        if ((pparams->post.allowed & POST_SHARE) && hdr &&
            (is_mediatype(hdr[0], DAVSHARING_CONTENT_TYPE) ||
             is_mediatype(hdr[0], "STR"))) {
            
            return dav_post_share(txn, pparams);
        }
        else if (pparams->post.bulk.data_prop && hdr &&
                 is_mediatype(hdr[0], "STR")) {
            
            return HTTP_FORBIDDEN;
        }
        else if (pparams->post.bulk.import && hdr) {
            
            return dav_post_import(txn, pparams);
        }
        else return HTTP_BAD_REQUEST;
    }

    if (!(pparams->post.allowed & POST_ADDMEMBER) ||
        !action || action->next || strcmp(action->s, "STR")) {
        return HTTP_BAD_REQUEST;
    }

    

    
    len = strlen(txn->req_tgt.path);
    txn->req_tgt.resource = txn->req_tgt.path + len;
    txn->req_tgt.reslen =
        snprintf(txn->req_tgt.resource, MAX_MAILBOX_PATH - len,
                 "STR", makeuuid(), pparams->mime_types[0].file_ext ?
                 pparams->mime_types[0].file_ext : "");

    
    txn->location = txn->req_tgt.path;

    ret = meth_put(txn, params);

    if (ret != HTTP_CREATED) txn->location = NULL;

    return ret;
}