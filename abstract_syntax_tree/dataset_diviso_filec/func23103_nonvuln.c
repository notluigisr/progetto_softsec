k5_asn1_encode_uint(asn1buf *buf, uintmax_t val)
{
    uintmax_t valcopy;
    int digit;

    valcopy = val;
    do {
        digit = valcopy & 0xFF;
        insert_byte(buf, digit);
        valcopy = valcopy >> 8;
    } while (valcopy != 0);

    
    if (digit & 0x80)
        insert_byte(buf, 0);
}