static int bio_zlib_flush(BIO *b)
	{
	BIO_ZLIB_CTX *ctx;
	int ret;
	z_stream *zout;
	ctx = (BIO_ZLIB_CTX *)b->ptr;
	
	if(!ctx->obuf || (ctx->odone && !ctx->ocount)) return 1;
	zout = &ctx->zout;
	BIO_clear_retry_flags(b);
	
	zout->next_in = NULL;
	zout->avail_in = 0;
	for(;;)
		{
		
		while(ctx->ocount)
			{
			ret = BIO_write(b->next_bio, ctx->optr, ctx->ocount);
			if(ret <= 0)
				{
				BIO_copy_next_retry(b);
				return ret;
				}
			ctx->optr += ret;
			ctx->ocount -= ret;
			}
		if(ctx->odone) return 1;

		

		
		ctx->optr = ctx->obuf;
		zout->next_out = ctx->obuf;
		zout->avail_out = ctx->obufsize;
		
		ret = deflate(zout, Z_FINISH);
		if(ret == Z_STREAM_END) ctx->odone = 1;
		else if(ret != Z_OK)
			{
			COMPerr(COMP_F_BIO_ZLIB_FLUSH,
						COMP_R_ZLIB_DEFLATE_ERROR);
			ERR_add_error_data(2, "STR", zError(ret));
			return 0;
			}
		ctx->ocount = ctx->obufsize - zout->avail_out;
		}
	}