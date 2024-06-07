FLAC_API FLAC__bool FLAC__stream_encoder_process(FLAC__StreamEncoder *encoder, const FLAC__int32 * const buffer[], unsigned samples)
{
	unsigned i, j = 0, channel;
	const unsigned channels = encoder->protected_->channels, blocksize = encoder->protected_->blocksize;

	FLAC__ASSERT(0 != encoder);
	FLAC__ASSERT(0 != encoder->private_);
	FLAC__ASSERT(0 != encoder->protected_);
	FLAC__ASSERT(encoder->protected_->state == FLAC__STREAM_ENCODER_OK);

	do {
		const unsigned n = flac_min(blocksize+OVERREAD_-encoder->private_->current_sample_number, samples-j);

		if(encoder->protected_->verify)
			append_to_verify_fifo_(&encoder->private_->verify.input_fifo, buffer, j, channels, n);

		for(channel = 0; channel < channels; channel++)
			memcpy(&encoder->private_->integer_signal[channel][encoder->private_->current_sample_number], &buffer[channel][j], sizeof(buffer[channel][0]) * n);

		if(encoder->protected_->do_mid_side_stereo) {
			FLAC__ASSERT(channels == 2);
			
			for(i = encoder->private_->current_sample_number; i <= blocksize && j < samples; i++, j++) {
				encoder->private_->integer_signal_mid_side[1][i] = buffer[0][j] - buffer[1][j];
				encoder->private_->integer_signal_mid_side[0][i] = (buffer[0][j] + buffer[1][j]) >> 1; 
			}
		}
		else
			j += n;

		encoder->private_->current_sample_number += n;

		
		if(encoder->private_->current_sample_number > blocksize) {
			FLAC__ASSERT(encoder->private_->current_sample_number == blocksize+OVERREAD_);
			FLAC__ASSERT(OVERREAD_ == 1); 
			if(!process_frame_(encoder, false, false))
				return false;
			
			for(channel = 0; channel < channels; channel++)
				encoder->private_->integer_signal[channel][0] = encoder->private_->integer_signal[channel][blocksize];
			if(encoder->protected_->do_mid_side_stereo) {
				encoder->private_->integer_signal_mid_side[0][0] = encoder->private_->integer_signal_mid_side[0][blocksize];
				encoder->private_->integer_signal_mid_side[1][0] = encoder->private_->integer_signal_mid_side[1][blocksize];
			}
			encoder->private_->current_sample_number = 1;
		}
	} while(j < samples);

	return true;
}