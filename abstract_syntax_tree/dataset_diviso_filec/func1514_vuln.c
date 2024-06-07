static int am_handle_login(request_rec *r)
{
    am_dir_cfg_rec *cfg = am_get_dir_cfg(r);
    char *idp_param;
    const char *idp;
    char *return_to;
    int is_passive;
    int ret;

    return_to = am_extract_query_parameter(r->pool, r->args, "STR");
    if(return_to == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "STR");
        return HTTP_BAD_REQUEST;
    }

    ret = am_urldecode(return_to);
    if(ret != OK) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "STR");
        return ret;
    }

    idp_param = am_extract_query_parameter(r->pool, r->args, "STR");
    if(idp_param != NULL) {
        ret = am_urldecode(idp_param);
        if(ret != OK) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "STR");
            return ret;
        }
    }

    ret = am_get_boolean_query_parameter(r, "STR", &is_passive, FALSE);
    if (ret != OK) {
        return ret;
    }

    if(idp_param != NULL) {
        idp = idp_param;
    } else if(cfg->discovery_url) {
        if(is_passive) {
            
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "STR");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        return am_start_disco(r, return_to);
    } else {
        
        idp = am_get_idp(r);
    }

    return am_send_login_authn_request(r, idp, return_to, is_passive);
}