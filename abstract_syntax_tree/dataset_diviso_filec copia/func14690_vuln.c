sf_flac_write_callback (const FLAC__StreamDecoder * UNUSED (decoder), const FLAC__Frame *frame, const int32_t * const buffer [], void *client_data)
{	SF_PRIVATE *psf = (SF_PRIVATE*) client_data ;
	FLAC_PRIVATE* pflac = (FLAC_PRIVATE*) psf->codec_data ;

	pflac->frame = frame ;
	pflac->bufferpos = 0 ;

	pflac->bufferbackup = SF_FALSE ;
	pflac->wbuffer = buffer ;

	flac_buffer_copy (psf) ;

	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE ;
} 