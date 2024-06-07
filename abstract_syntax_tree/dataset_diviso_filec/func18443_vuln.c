static json_t *parse_json(lex_t *lex, size_t flags, json_error_t *error)
{
    json_t *result;

    lex_scan(lex, error);
    if(!(flags & JSON_DECODE_ANY)) {
        if(lex->token != '[' && lex->token != '{') {
            error_set(error, lex, "STR");
            return NULL;
        }
    }

    result = parse_value(lex, flags, error);
    if(!result)
        return NULL;

    if(!(flags & JSON_DISABLE_EOF_CHECK)) {
        lex_scan(lex, error);
        if(lex->token != TOKEN_EOF) {
            error_set(error, lex, "STR");
            json_decref(result);
            return NULL;
        }
    }

    if(error) {
        
        error->position = (int)lex->stream.position;
    }

    return result;
}