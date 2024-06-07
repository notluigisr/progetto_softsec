static int fbo_emulate_format_unit(struct tcmu_device *dev, uint8_t *cdb,
				   struct iovec *iovec, size_t iov_cnt,
				   uint8_t *sense)
{
	struct fbo_state *state = tcmu_get_dev_private(dev);
	pthread_t thr;
	uint8_t param_list[12];

	
	if (state->flags & FBO_READ_ONLY)
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_CANT_WRITE_INCOMPATIBLE_FORMAT,
					   NULL);

	if (!(cdb[1] & 0x10) || ((cdb[1] & 0x07) != 1) || cdb[3] || cdb[4])
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_CDB, NULL);

	if (tcmu_memcpy_from_iovec(param_list, 12, iovec, iov_cnt) < 12)
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_PARAMETER_LIST_LENGTH_ERROR,
					   NULL);

	if (!(param_list[1] & 0x80) && (param_list[1] & 0x7c))
		
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_PARAMETER_LIST,
					   NULL);

	if (param_list[1] & 0x1c)
		
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_PARAMETER_LIST,
					   NULL);

	if (be16toh(*(uint16_t *)&param_list[2]) != 8)
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_PARAMETER_LIST,
					   NULL);

	if (param_list[8])
		
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_PARAMETER_LIST,
					   NULL);

	if ((cdb[1] & 0x08 || !(param_list[1] & 0x20)) &&
	    be32toh(*(uint32_t *)&param_list[4]) != state->num_lbas)
		
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_PARAMETER_LIST,
					   NULL);

	if ((((uint32_t)param_list[9] << 16) +
	     be16toh(*(uint16_t *)&param_list[10])) != state->block_size)
		
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_PARAMETER_LIST,
					   NULL);

	pthread_mutex_lock(&state->state_mtx);
	
	if (state->flags & FBO_FORMATTING) {
		pthread_mutex_unlock(&state->state_mtx);
		return tcmu_set_sense_data(sense, NOT_READY,
					   ASC_NOT_READY_FORMAT_IN_PROGRESS,
					   &state->format_progress);
	}
	state->format_progress = 0;
	state->flags |= FBO_FORMATTING;
	pthread_mutex_unlock(&state->state_mtx);

	if (param_list[1] & 0x02) {
		
		pthread_create(&thr, NULL, fbo_async_format, dev);

		return SAM_STAT_GOOD;
	}

	return fbo_do_format(dev, sense);
}