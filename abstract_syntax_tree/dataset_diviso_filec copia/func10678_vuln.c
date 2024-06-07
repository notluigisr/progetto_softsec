word32 DecodeDSA_Signature(byte* decoded, const byte* encoded, word32 sz)
{
    Source source(encoded, sz);

    if (source.next() != (SEQUENCE | CONSTRUCTED)) {
        source.SetError(SEQUENCE_E);
        return 0;
    }

    GetLength(source);  

    
    if (source.next() != INTEGER) {
        source.SetError(INTEGER_E);
        return 0;
    }
    word32 rLen = GetLength(source);
    if (rLen != 20) {
        if (rLen == 21) {       
            source.next();
            --rLen;
        }
        else if (rLen == 19) {  
            decoded[0] = 0;
            decoded++;
        }
        else {
            source.SetError(DSA_SZ_E);
            return 0;
        }
    }
    memcpy(decoded, source.get_buffer() + source.get_index(), rLen);
    source.advance(rLen);

    
    if (source.next() != INTEGER) {
        source.SetError(INTEGER_E);
        return 0;
    }
    word32 sLen = GetLength(source);
    if (sLen != 20) {
        if (sLen == 21) {
            source.next();          
            --sLen;
        }
        else if (sLen == 19) {
            decoded[rLen] = 0;      
            decoded++;
        }
        else {
            source.SetError(DSA_SZ_E);
            return 0;
        }
    }
    memcpy(decoded + rLen, source.get_buffer() + source.get_index(), sLen);
    source.advance(sLen);

    return 40;
}