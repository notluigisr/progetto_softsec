static int read_capacity_10(struct scsi_disk *sdkp, struct scsi_device *sdp,
						unsigned char *buffer)
{
	unsigned char cmd[16];
	struct scsi_sense_hdr sshdr;
	int sense_valid = 0;
	int the_result;
	int retries = 3, reset_retries = READ_CAPACITY_RETRIES_ON_RESET;
	sector_t lba;
	unsigned sector_size;

	do {
		cmd[0] = READ_CAPACITY;
		memset(&cmd[1], 0, 9);
		memset(buffer, 0, 8);

		the_result = scsi_execute_req(sdp, cmd, DMA_FROM_DEVICE,
					buffer, 8, &sshdr,
					SD_TIMEOUT, SD_MAX_RETRIES, NULL);

		if (media_not_present(sdkp, &sshdr))
			return -ENODEV;

		if (the_result) {
			sense_valid = scsi_sense_valid(&sshdr);
			if (sense_valid &&
			    sshdr.sense_key == UNIT_ATTENTION &&
			    sshdr.asc == 0x29 && sshdr.ascq == 0x00)
				
				if (--reset_retries > 0)
					continue;
		}
		retries--;

	} while (the_result && retries);

	if (the_result) {
		sd_printk(KERN_NOTICE, sdkp, "STR");
		read_capacity_error(sdkp, sdp, &sshdr, sense_valid, the_result);
		return -EINVAL;
	}

	sector_size = get_unaligned_be32(&buffer[4]);
	lba = get_unaligned_be32(&buffer[0]);

	if (sdp->no_read_capacity_16 && (lba == 0xffffffff)) {
		
		sdkp->capacity = 0;
		sdkp->physical_block_size = sector_size;
		return sector_size;
	}

	if ((sizeof(sdkp->capacity) == 4) && (lba == 0xffffffff)) {
		sd_printk(KERN_ERR, sdkp, "STR"
			"STR"
			"STR");
		sdkp->capacity = 0;
		return -EOVERFLOW;
	}

	sdkp->capacity = lba + 1;
	sdkp->physical_block_size = sector_size;
	return sector_size;
}