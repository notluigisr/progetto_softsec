is_anyone_waiting_for_metafile (NautilusDirectory *directory)
{
	if (directory->details->call_when_ready_counters[REQUEST_METAFILE] > 0) {
		return TRUE;
	}

	if (directory->details->monitor_counters[REQUEST_METAFILE] > 0) {
		return TRUE;
	}

	return FALSE;
}