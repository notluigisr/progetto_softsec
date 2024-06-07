static void spotcheck_subframe_estimate_(
	FLAC__StreamEncoder *encoder,
	unsigned blocksize,
	unsigned subframe_bps,
	const FLAC__Subframe *subframe,
	unsigned estimate
)
{
	FLAC__bool ret;
	FLAC__BitWriter *frame = FLAC__bitwriter_new();
	if(frame == 0) {
		fprintf(stderr, "STR");
		return;
	}
	if(!FLAC__bitwriter_init(frame)) {
		fprintf(stderr, "STR");
		return;
	}
	ret = add_subframe_(encoder, blocksize, subframe_bps, subframe, frame);
	FLAC__ASSERT(ret);
	{
		const unsigned actual = FLAC__bitwriter_get_input_bits_unconsumed(frame);
		if(estimate != actual)
			fprintf(stderr, "STR", encoder->private_->current_frame_number, FLAC__SubframeTypeString[subframe->type], estimate, actual, (int)actual-(int)estimate);
	}
	FLAC__bitwriter_delete(frame);
}