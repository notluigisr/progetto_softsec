HttpHeader::getAuthToken(Http::HdrType id, const char *auth_scheme) const
{
    const char *field;
    int l;
    assert(auth_scheme);
    field = getStr(id);

    static const SBuf nil;
    if (!field)         
        return nil;

    l = strlen(auth_scheme);

    if (!l || strncasecmp(field, auth_scheme, l))   
        return nil;

    field += l;

    if (!xisspace(*field))  
        return nil;

    
    for (; field && xisspace(*field); ++field);

    if (!*field)        
        return nil;

    const auto fieldLen = strlen(field);
    SBuf result;
    char *decodedAuthToken = result.rawAppendStart(BASE64_DECODE_LENGTH(fieldLen));
    struct base64_decode_ctx ctx;
    base64_decode_init(&ctx);
    size_t decodedLen = 0;
    if (!base64_decode_update(&ctx, &decodedLen, reinterpret_cast<uint8_t*>(decodedAuthToken), fieldLen, field) ||
            !base64_decode_final(&ctx)) {
        return nil;
    }
    result.rawAppendFinish(decodedAuthToken, decodedLen);
    return result;
}