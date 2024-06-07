FLAC__StreamDecoderWriteStatus flac_decoder_write_callback(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client_data)
{
	EncoderSession *e = (EncoderSession*)client_data;
    FLACDecoderData *data = &e->fmt.flac.client_data;
	FLAC__uint64 n = min(data->samples_left_to_process, frame->header.blocksize);
	(void)decoder;

	if(!EncoderSession_process(e, buffer, (unsigned)n)) {
		print_error_with_state(e, "STR");
		data->fatal_error = true;
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}

	data->samples_left_to_process -= n;
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}