static int asn1_template_ex_d2i(ASN1_VALUE **val,
                                const unsigned char **in, long inlen,
                                const ASN1_TEMPLATE *tt, char opt,
                                ASN1_TLC *ctx)
{
    int flags, aclass;
    int ret;
    long len;
    const unsigned char *p, *q;
    char exp_eoc;
    if (!val)
        return 0;
    flags = tt->flags;
    aclass = flags & ASN1_TFLG_TAG_CLASS;

    p = *in;

    
    if (flags & ASN1_TFLG_EXPTAG) {
        char cst;
        
        ret = asn1_check_tlen(&len, NULL, NULL, &exp_eoc, &cst,
                              &p, inlen, tt->tag, aclass, opt, ctx);
        q = p;
        if (!ret) {
            ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I, ERR_R_NESTED_ASN1_ERROR);
            return 0;
        } else if (ret == -1)
            return -1;
        if (!cst) {
            ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I,
                    ASN1_R_EXPLICIT_TAG_NOT_CONSTRUCTED);
            return 0;
        }
        
        ret = asn1_template_noexp_d2i(val, &p, len, tt, 0, ctx);
        if (!ret) {
            ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I, ERR_R_NESTED_ASN1_ERROR);
            return 0;
        }
        
        len -= p - q;
        if (exp_eoc) {
            
            if (!asn1_check_eoc(&p, len)) {
                ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I, ASN1_R_MISSING_EOC);
                goto err;
            }
        } else {
            
            if (len) {
                ASN1err(ASN1_F_ASN1_TEMPLATE_EX_D2I,
                        ASN1_R_EXPLICIT_LENGTH_MISMATCH);
                goto err;
            }
        }
    } else
        return asn1_template_noexp_d2i(val, in, inlen, tt, opt, ctx);

    *in = p;
    return 1;

 err:
    return 0;
}