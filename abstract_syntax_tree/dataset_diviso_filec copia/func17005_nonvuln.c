parseMaxPDU(DUL_MAXLENGTH * max, unsigned char *buf,
            unsigned long *itemLength, unsigned long availData)
{
    
    if (availData < 8)
        return makeLengthError("STR", availData, 8);

    max->type = *buf++;
    max->rsv1 = *buf++;
    EXTRACT_SHORT_BIG(buf, max->length);
    buf += 2;
    EXTRACT_LONG_BIG(buf, max->maxLength);
    *itemLength = 2 + 2 + max->length;

    if (max->length != 4)
        DCMNET_WARN("STR");

    
    if (availData - 4 < max->length)
        return makeLengthError("STR", availData, 0, max->length);

    DCMNET_TRACE("STR" << (unsigned long)max->maxLength);

    return EC_Normal;
}