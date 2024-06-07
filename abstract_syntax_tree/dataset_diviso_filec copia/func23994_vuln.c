rdpsnd_process_ping(STREAM in)
{
	uint16 tick;
	STREAM out;

	in_uint16_le(in, tick);

	DEBUG_SOUND(("STR", (unsigned) tick));

	out = rdpsnd_init_packet(RDPSND_PING | 0x2300, 4);
	out_uint16_le(out, tick);
	out_uint16_le(out, 0);
	s_mark_end(out);
	rdpsnd_send(out);

	DEBUG_SOUND(("STR", (unsigned) tick));
}