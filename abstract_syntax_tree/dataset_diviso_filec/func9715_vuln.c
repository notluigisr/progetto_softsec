SetWALFileNameForCleanup(void)
{
	uint32		tli = 1,
				log = 0,
				seg = 0;
	uint32		log_diff = 0,
				seg_diff = 0;
	bool		cleanup = false;

	if (restartWALFileName)
	{
		
		if (strcmp(restartWALFileName, nextWALFileName) > 0)
			return false;

		strcpy(exclusiveCleanupFileName, restartWALFileName);
		return true;
	}

	if (keepfiles > 0)
	{
		sscanf(nextWALFileName, "STR", &tli, &log, &seg);
		if (tli > 0 && seg > 0)
		{
			log_diff = keepfiles / MaxSegmentsPerLogFile;
			seg_diff = keepfiles % MaxSegmentsPerLogFile;
			if (seg_diff > seg)
			{
				log_diff++;
				seg = MaxSegmentsPerLogFile - (seg_diff - seg);
			}
			else
				seg -= seg_diff;

			if (log >= log_diff)
			{
				log -= log_diff;
				cleanup = true;
			}
			else
			{
				log = 0;
				seg = 0;
			}
		}
	}

	XLogFileName(exclusiveCleanupFileName, tli, log, seg);

	return cleanup;
}