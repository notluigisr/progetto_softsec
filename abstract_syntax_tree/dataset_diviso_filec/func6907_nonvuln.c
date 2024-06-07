int wc_ecc_sig_size(ecc_key* key)
{
    int maxSigSz;
    int orderBits, keySz;

    if (key == NULL || key->dp == NULL)
        return 0;

    
    
    keySz = key->dp->size;
    orderBits = wc_ecc_get_curve_order_bit_count(key->dp);
    if (orderBits > keySz * 8) {
        keySz = (orderBits + 7) / 8;
    }
    
    maxSigSz = (keySz * 2) + SIG_HEADER_SZ;
    if ((orderBits % 8) == 0) {
        
        maxSigSz += ECC_MAX_PAD_SZ;
    }
    
    if (maxSigSz < (128 + 2)) {
        maxSigSz -= 1;
    }

    return maxSigSz;
}