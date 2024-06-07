static uint32_t get_eid(uint32_t eid)
{
	if (eid <= 15) {
		return eid;
	}

	switch (eid) {
	case AD_DEV:
		return ADEID_PRIVDEV;
	case AD_INO:
		return ADEID_PRIVINO;
	case AD_SYN:
		return ADEID_PRIVSYN;
	case AD_ID:
		return ADEID_PRIVID;
	default:
		break;
	}

	return 0;
}