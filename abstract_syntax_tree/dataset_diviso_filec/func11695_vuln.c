static avifBool avifParseImageGridBox(avifImageGrid * grid, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    uint8_t version, flags;
    CHECK(avifROStreamRead(&s, &version, 1)); 
    if (version != 0) {
        return AVIF_FALSE;
    }
    CHECK(avifROStreamRead(&s, &flags, 1));         
    CHECK(avifROStreamRead(&s, &grid->rows, 1));    
    CHECK(avifROStreamRead(&s, &grid->columns, 1)); 
    ++grid->rows;
    ++grid->columns;

    uint32_t fieldLength = ((flags & 1) + 1) * 16;
    if (fieldLength == 16) {
        uint16_t outputWidth16, outputHeight16;
        CHECK(avifROStreamReadU16(&s, &outputWidth16));  
        CHECK(avifROStreamReadU16(&s, &outputHeight16)); 
        grid->outputWidth = outputWidth16;
        grid->outputHeight = outputHeight16;
    } else {
        if (fieldLength != 32) {
            
            return AVIF_FALSE;
        }
        CHECK(avifROStreamReadU32(&s, &grid->outputWidth));  
        CHECK(avifROStreamReadU32(&s, &grid->outputHeight)); 
    }
    return AVIF_TRUE;
}