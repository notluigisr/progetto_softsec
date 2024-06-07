static void print_stats(const EncoderSession *encoder_session)
{
	if(flac__utils_verbosity_ >= 2) {
		char ratiostr[16];

		FLAC__ASSERT(encoder_session->total_samples_to_encode > 0);

		if (encoder_session->compression_ratio > 0.0)
			flac_snprintf(ratiostr, sizeof(ratiostr), "STR", encoder_session->compression_ratio);
		else
			flac_snprintf(ratiostr, sizeof(ratiostr), "STR");

		if(encoder_session->samples_written == encoder_session->total_samples_to_encode) {
			stats_print_name(2, encoder_session->inbasefilename);
			stats_print_info(2, "STR",
				encoder_session->verify? "STR",
				encoder_session->bytes_written,
				ratiostr
			);
		}
		else {
			stats_print_name(2, encoder_session->inbasefilename);
			stats_print_info(2, "STR", (unsigned)floor(encoder_session->progress * 100.0 + 0.5), ratiostr);
		}
	}
}