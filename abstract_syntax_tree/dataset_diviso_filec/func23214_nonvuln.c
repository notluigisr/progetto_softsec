FLAC__bool flac_decoder_eof_callback(const FLAC__StreamDecoder *decoder, void *client_data)
{
	EncoderSession *e = (EncoderSession*)client_data;
	(void)decoder;

	return feof(e->fin)? true : false;
}