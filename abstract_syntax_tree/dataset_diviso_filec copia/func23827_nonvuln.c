int EncodePolicyOID(byte *out, word32 *outSz, const char *in, void* heap)
{
    word32 val, idx = 0, nb_val;
    char *token, *str, *ptr;
    word32 len;

    (void)heap;

    if (out == NULL || outSz == NULL || *outSz < 2 || in == NULL)
        return BAD_FUNC_ARG;

    
    len = (word32)XSTRLEN(in);
    str = (char *)XMALLOC(len+1, heap, DYNAMIC_TYPE_TMP_BUFFER);
    if (str == NULL)
        return MEMORY_E;
    XMEMCPY(str, in, len+1);

    nb_val = 0;

    
    token = XSTRTOK(str, "STR", &ptr);
    while (token != NULL)
    {
        val = (word32)XATOI(token);

        if (nb_val == 0) {
            if (val > 2) {
                XFREE(str, heap, DYNAMIC_TYPE_TMP_BUFFER);
                return ASN_OBJECT_ID_E;
            }

            out[idx] = (byte)(40 * val);
        }
        else if (nb_val == 1) {
            if (val > 127) {
                XFREE(str, heap, DYNAMIC_TYPE_TMP_BUFFER);
                return ASN_OBJECT_ID_E;
            }

            if (idx > *outSz) {
                XFREE(str, heap, DYNAMIC_TYPE_TMP_BUFFER);
                return BUFFER_E;
            }

            out[idx++] += (byte)val;
        }
        else {
            word32  tb = 0, x;
            int     i = 0;
            byte    oid[MAX_OID_SZ];

            while (val >= 128) {
                x = val % 128;
                val /= 128;
                oid[i++] = (byte) (((tb++) ? 0x80 : 0) | x);
            }

            if ((idx+(word32)i) >= *outSz) {
                XFREE(str, heap, DYNAMIC_TYPE_TMP_BUFFER);
                return BUFFER_E;
            }

            oid[i] = (byte) (((tb++) ? 0x80 : 0) | val);

            
            while (i >= 0)
                out[idx++] = oid[i--];
        }

        token = XSTRTOK(NULL, "STR", &ptr);
        nb_val++;
    }

    *outSz = idx;

    XFREE(str, heap, DYNAMIC_TYPE_TMP_BUFFER);
    return 0;
}