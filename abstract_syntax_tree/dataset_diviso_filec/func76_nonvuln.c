mcs_recv_aucf(uint16 * mcs_userid)
{
	RD_BOOL is_fastpath;
	uint8 fastpath_hdr;
	uint8 opcode, result;
	STREAM s;

	logger(Protocol, Debug, "STR", __func__);
	s = iso_recv(&is_fastpath, &fastpath_hdr);

	if (s == NULL)
		return False;

	in_uint8(s, opcode);
	if ((opcode >> 2) != MCS_AUCF)
	{
		logger(Protocol, Error, "STR", opcode);
		return False;
	}

	in_uint8(s, result);
	if (result != 0)
	{
		logger(Protocol, Error, "STR", result);
		return False;
	}

	if (opcode & 2)
		in_uint16_be(s, *mcs_userid);

	return s_check_end(s);
}