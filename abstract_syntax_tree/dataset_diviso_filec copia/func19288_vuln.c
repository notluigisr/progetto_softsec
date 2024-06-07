xmlZMemBuffGetContent( xmlZMemBuffPtr buff, char ** data_ref ) {

    int		zlgth = -1;
    int		z_err;

    if ( ( buff == NULL ) || ( data_ref == NULL ) )
	return ( -1 );

    

    do
    {
	z_err = deflate( &buff->zctrl, Z_FINISH );
	if ( z_err == Z_OK ) {
	    

	    if ( xmlZMemBuffExtend( buff, buff->size ) == -1 )
		return ( -1 );
	}
    }
    while ( z_err == Z_OK );

    

    if ( z_err == Z_STREAM_END ) {

	

	if ( buff->zctrl.avail_out < ( 2 * sizeof( unsigned long ) ) ) {
	    if ( xmlZMemBuffExtend(buff, (2 * sizeof(unsigned long))) == -1 )
		return ( -1 );
	}

	

	append_reverse_ulong( buff, buff->crc );
	append_reverse_ulong( buff, buff->zctrl.total_in );

	zlgth = buff->zctrl.next_out - buff->zbuff;
	*data_ref = (char *)buff->zbuff;
    }

    else {
	xmlChar msg[500];
	xmlStrPrintf(msg, 500,
		    (const xmlChar *) "STR",
		    "STR", z_err );
	xmlIOErr(XML_IO_WRITE, (const char *) msg);
    }

    return ( zlgth );
}