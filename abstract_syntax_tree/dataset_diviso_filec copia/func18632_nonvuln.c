ngx_http_lua_copy_in_file_request_body(ngx_http_request_t *r)
{
    ngx_temp_file_t     *tf;

    ngx_http_request_body_t   *body;

    tf = r->request_body->temp_file;

    if (!tf->persistent || !tf->clean) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "STR");

        return NGX_ERROR;
    }

    body = ngx_palloc(r->pool, sizeof(ngx_http_request_body_t));
    if (body == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(body, r->request_body, sizeof(ngx_http_request_body_t));

    body->temp_file = ngx_palloc(r->pool, sizeof(ngx_temp_file_t));
    if (body->temp_file == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(body->temp_file, tf, sizeof(ngx_temp_file_t));
    dd("STR", body->temp_file->file.fd);

    r->request_body = body;

    return NGX_OK;
}