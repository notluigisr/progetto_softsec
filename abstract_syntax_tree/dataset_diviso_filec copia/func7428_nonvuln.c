status writeJsonObjElm(CtxJson *ctx, const char *key,
                       const void *value, const UA_DataType *type){
    return writeJsonKey(ctx, key) | encodeJsonInternal(value, type, ctx);
}