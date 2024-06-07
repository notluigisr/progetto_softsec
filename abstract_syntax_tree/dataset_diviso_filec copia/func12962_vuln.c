WRITE_JSON_ELEMENT(ObjStart) {
    
    ctx->depth++;
    ctx->commaNeeded[ctx->depth] = false;
    return writeChar(ctx, '{');
}