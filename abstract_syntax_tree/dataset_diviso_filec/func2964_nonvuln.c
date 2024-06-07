static void ssl_write_hostname_ext( ssl_context *ssl,
                                    unsigned char *buf,
                                    size_t *olen )
{
    unsigned char *p = buf;
    const unsigned char *end = ssl->out_msg + SSL_MAX_CONTENT_LEN;

    *olen = 0;

    if( ssl->hostname == NULL )
        return;

    SSL_DEBUG_MSG( 3, ( "STR",
                   ssl->hostname ) );

    if( end < p || (size_t)( end - p ) < ssl->hostname_len + 9 )
    {
         SSL_DEBUG_MSG( 1, ( "STR" ) );
         return;
    }

    
    *p++ = (unsigned char)( ( TLS_EXT_SERVERNAME >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( TLS_EXT_SERVERNAME      ) & 0xFF );

    *p++ = (unsigned char)( ( (ssl->hostname_len + 5) >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( (ssl->hostname_len + 5)      ) & 0xFF );

    *p++ = (unsigned char)( ( (ssl->hostname_len + 3) >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( (ssl->hostname_len + 3)      ) & 0xFF );

    *p++ = (unsigned char)( ( TLS_EXT_SERVERNAME_HOSTNAME ) & 0xFF );
    *p++ = (unsigned char)( ( ssl->hostname_len >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( ssl->hostname_len      ) & 0xFF );

    memcpy( p, ssl->hostname, ssl->hostname_len );

    *olen = ssl->hostname_len + 9;
}