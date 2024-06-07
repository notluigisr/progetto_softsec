tokenize(ParseCtx *parseCtx, CtxJson *ctx, const UA_ByteString *src) {
    
    ctx->pos = &src->data[0];
    ctx->end = &src->data[src->length];
    ctx->depth = 0;
    parseCtx->tokenCount = 0;
    parseCtx->index = 0;

    
    jsmn_parser p;
    jsmn_init(&p);
    parseCtx->tokenCount = (UA_Int32)
        jsmn_parse(&p, (char*)src->data, src->length,
                   parseCtx->tokenArray, UA_JSON_MAXTOKENCOUNT);
    
    if(parseCtx->tokenCount < 0) {
        if(parseCtx->tokenCount == JSMN_ERROR_NOMEM)
            return UA_STATUSCODE_BADOUTOFMEMORY;
        return UA_STATUSCODE_BADDECODINGERROR;
    }
    
    return UA_STATUSCODE_GOOD;
}