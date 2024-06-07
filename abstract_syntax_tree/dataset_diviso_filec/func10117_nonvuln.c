static void dump_tokens(request_rec *r, apr_array_header_t *tokens)
{
    apr_size_t i;
    
    for (i = 0; i < tokens->nelts; i++) {
        Token token = APR_ARRAY_IDX(tokens, i, Token);
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "STR", i,
                      token_type_str(token.type), token.str,
                      token.offset, token.len);
    }
}