int wc_InitCert(Cert* cert)
{
#ifdef WOLFSSL_MULTI_ATTRIB
    int i = 0;
#endif
    if (cert == NULL) {
        return BAD_FUNC_ARG;
    }

    XMEMSET(cert, 0, sizeof(Cert));

    cert->version    = 2;   
#ifndef NO_SHA
    cert->sigType    = CTC_SHAwRSA;
#elif !defined(NO_SHA256)
    cert->sigType    = CTC_SHA256wRSA;
#else
    cert->sigType    = 0;
#endif
    cert->daysValid  = 500;
    cert->selfSigned = 1;
    cert->keyType    = RSA_KEY;

    cert->issuer.countryEnc = CTC_PRINTABLE;
    cert->issuer.stateEnc = CTC_UTF8;
    cert->issuer.localityEnc = CTC_UTF8;
    cert->issuer.surEnc = CTC_UTF8;
    cert->issuer.orgEnc = CTC_UTF8;
    cert->issuer.unitEnc = CTC_UTF8;
    cert->issuer.commonNameEnc = CTC_UTF8;

    cert->subject.countryEnc = CTC_PRINTABLE;
    cert->subject.stateEnc = CTC_UTF8;
    cert->subject.localityEnc = CTC_UTF8;
    cert->subject.surEnc = CTC_UTF8;
    cert->subject.orgEnc = CTC_UTF8;
    cert->subject.unitEnc = CTC_UTF8;
    cert->subject.commonNameEnc = CTC_UTF8;

#ifdef WOLFSSL_MULTI_ATTRIB
    for (i = 0; i < CTC_MAX_ATTRIB; i++) {
        cert->issuer.name[i].type   = CTC_UTF8;
        cert->subject.name[i].type  = CTC_UTF8;
    }
#endif 

#ifdef WOLFSSL_HEAP_TEST
    cert->heap = (void*)WOLFSSL_HEAP_TEST;
#endif

    return 0;
}