static int fbo_synchronize_cache(struct tcmu_device *dev, uint8_t *cdb,
				 uint8_t *sense)
{
	struct fbo_state *state = tcmu_get_dev_private(dev);
	pthread_t thr;

	
	
	if (cdb[1] & 0x01)
		return tcmu_set_sense_data(sense, ILLEGAL_REQUEST,
					   ASC_INVALID_FIELD_IN_CDB, NULL);

	if (cdb[1] & 0x02) {
		
		pthread_create(&thr, NULL, fbo_async_sync_cache, dev);

		return SAM_STAT_GOOD;
	}

	return fbo_do_sync(state, sense);
}