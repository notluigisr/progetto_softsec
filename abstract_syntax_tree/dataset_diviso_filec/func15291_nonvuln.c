PJ_DEF(pj_bool_t) pj_ssl_cipher_is_supported(pj_ssl_cipher cipher)
{
    unsigned i;

    ssl_ciphers_populate();

    for (i = 0; i < ssl_cipher_num; ++i) {
	if (cipher == ssl_ciphers[i].id)
	    return PJ_TRUE;
    }

    return PJ_FALSE;
}