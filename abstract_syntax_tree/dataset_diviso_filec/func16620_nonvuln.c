static int asn1_check_tlen(long *olen, int *otag, unsigned char *oclass,
                           char *inf, char *cst,
                           const unsigned char **in, long len,
                           int exptag, int expclass, char opt, ASN1_TLC *ctx)
{
    int i;
    int ptag, pclass;
    long plen;
    const unsigned char *p, *q;
    p = *in;
    q = p;

    if (ctx && ctx->valid) {
        i = ctx->ret;
        plen = ctx->plen;
        pclass = ctx->pclass;
        ptag = ctx->ptag;
        p += ctx->hdrlen;
    } else {
        i = ASN1_get_object(&p, &plen, &ptag, &pclass, len);
        if (ctx) {
            ctx->ret = i;
            ctx->plen = plen;
            ctx->pclass = pclass;
            ctx->ptag = ptag;
            ctx->hdrlen = p - q;
            ctx->valid = 1;
            
            if (!(i & 0x81) && ((plen + ctx->hdrlen) > len)) {
                ASN1err(ASN1_F_ASN1_CHECK_TLEN, ASN1_R_TOO_LONG);
                asn1_tlc_clear(ctx);
                return 0;
            }
        }
    }

    if (i & 0x80) {
        ASN1err(ASN1_F_ASN1_CHECK_TLEN, ASN1_R_BAD_OBJECT_HEADER);
        asn1_tlc_clear(ctx);
        return 0;
    }
    if (exptag >= 0) {
        if ((exptag != ptag) || (expclass != pclass)) {
            
            if (opt)
                return -1;
            asn1_tlc_clear(ctx);
            ASN1err(ASN1_F_ASN1_CHECK_TLEN, ASN1_R_WRONG_TAG);
            return 0;
        }
        
        asn1_tlc_clear(ctx);
    }

    if (i & 1)
        plen = len - (p - q);

    if (inf)
        *inf = i & 1;

    if (cst)
        *cst = i & V_ASN1_CONSTRUCTED;

    if (olen)
        *olen = plen;

    if (oclass)
        *oclass = pclass;

    if (otag)
        *otag = ptag;

    *in = p;
    return 1;
}