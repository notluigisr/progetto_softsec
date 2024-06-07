ngx_mail_auth_plain(ngx_mail_session_t *s, ngx_connection_t *c, ngx_uint_t n)
{
    u_char     *p, *last;
    ngx_str_t  *arg, plain;

    arg = s->args.elts;

#if (NGX_DEBUG_MAIL_PASSWD)
    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "STR", &arg[n]);
#endif

    plain.data = ngx_pnalloc(c->pool, ngx_base64_decoded_length(arg[n].len));
    if (plain.data == NULL) {
        return NGX_ERROR;
    }

    if (ngx_decode_base64(&plain, &arg[n]) != NGX_OK) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
            "STR");
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    p = plain.data;
    last = p + plain.len;

    while (p < last && *p++) {  }

    if (p == last) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
                      "STR");
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    s->login.data = p;

    while (p < last && *p) { p++; }

    if (p == last) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
                      "STR");
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    s->login.len = p++ - s->login.data;

    s->passwd.len = last - p;
    s->passwd.data = p;

#if (NGX_DEBUG_MAIL_PASSWD)
    ngx_log_debug2(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "STR", &s->login, &s->passwd);
#endif

    return NGX_DONE;
}