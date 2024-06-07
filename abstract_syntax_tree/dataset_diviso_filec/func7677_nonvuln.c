DECODE_JSON(Byte) {
    CHECK_TOKEN_BOUNDS;
    CHECK_PRIMITIVE;
    size_t tokenSize;
    char* tokenData;
    GET_TOKEN(tokenData, tokenSize);

    UA_UInt64 out = 0;
    UA_StatusCode s = parseUnsignedInteger(tokenData, tokenSize, &out);
    *dst = (UA_Byte)out;

    if(moveToken)
        parseCtx->index++;
    return s;
}