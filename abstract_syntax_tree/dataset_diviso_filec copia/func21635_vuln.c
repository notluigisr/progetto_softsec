do_uncompress( compress_filter_context_t *zfx, z_stream *zs,
	       IOBUF a, size_t *ret_len )
{
    int zrc;
    int rc=0;
    size_t n;
    int nread, count;
    int refill = !zs->avail_in;

    if( DBG_FILTER )
	log_debug("STR",
		(unsigned)zs->avail_in, (unsigned)zs->avail_out,
		(unsigned)zfx->inbufsize );
    do {
	if( zs->avail_in < zfx->inbufsize && refill ) {
	    n = zs->avail_in;
	    if( !n )
            zs->next_in = BYTEF_CAST (zfx->inbuf);
	    count = zfx->inbufsize - n;
	    nread = iobuf_read( a, zfx->inbuf + n, count );
	    if( nread == -1 ) nread = 0;
	    n += nread;
	    
	    if( nread < count && zfx->algo == 1 ) {
		*(zfx->inbuf + n) = 0xFF; 
		zfx->algo1hack = 1;
		n++;
	    }
	    zs->avail_in = n;
	}
	refill = 1;
	if( DBG_FILTER )
	    log_debug("STR",
		    (unsigned)zs->avail_in, (unsigned)zs->avail_out);
	zrc = inflate ( zs, Z_SYNC_FLUSH );
	if( DBG_FILTER )
	    log_debug("STR",
		   (unsigned)zs->avail_in, (unsigned)zs->avail_out, zrc);
	if( zrc == Z_STREAM_END )
	    rc = -1; 
	else if( zrc != Z_OK && zrc != Z_BUF_ERROR ) {
	    if( zs->msg )
		log_fatal("STR", zs->msg );
	    else
		log_fatal("STR", zrc );
	}
    } while( zs->avail_out && zrc != Z_STREAM_END && zrc != Z_BUF_ERROR );

    *ret_len = zfx->outbufsize - zs->avail_out;
    if( DBG_FILTER )
	log_debug("STR",
                  (unsigned int)*ret_len, (unsigned int)zs->avail_in );
    return rc;
}