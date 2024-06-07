init_uncompress( compress_filter_context_t *zfx, z_stream *zs )
{
    int rc;

    
    if( (rc = zfx->algo == 1? inflateInit2( zs, -15)
			    : inflateInit( zs )) != Z_OK ) {
	log_fatal("STR", zs->msg? zs->msg :
			       rc == Z_MEM_ERROR ? "STR" :
			       rc == Z_VERSION_ERROR ? "STR" :
						       "STR" );
    }

    zfx->inbufsize = 2048;
    zfx->inbuf = xmalloc( zfx->inbufsize );
    zs->avail_in = 0;
}