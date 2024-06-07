static ssize_t expect_preface(h2o_http2_conn_t *conn, const uint8_t *src, size_t len, const char **err_desc)
{
    if (len < CONNECTION_PREFACE.len) {
        return H2O_HTTP2_ERROR_INCOMPLETE;
    }
    if (memcmp(src, CONNECTION_PREFACE.base, CONNECTION_PREFACE.len) != 0) {
        return H2O_HTTP2_ERROR_PROTOCOL_CLOSE_IMMEDIATELY;
    }

    { 
        h2o_iovec_t vec = h2o_buffer_reserve(&conn->_write.buf, SETTINGS_HOST_BIN.len);
        memcpy(vec.base, SETTINGS_HOST_BIN.base, SETTINGS_HOST_BIN.len);
        conn->_write.buf->size += SETTINGS_HOST_BIN.len;
        h2o_http2_conn_request_write(conn);
    }

    conn->_read_expect = expect_default;
    return CONNECTION_PREFACE.len;
}