void libworker_fg_done_cb(void* ATTR_UNUSED(arg), int ATTR_UNUSED(rcode),
	sldns_buffer* ATTR_UNUSED(buf), enum sec_status ATTR_UNUSED(s),
	char* ATTR_UNUSED(why_bogus), int ATTR_UNUSED(was_ratelimited))
{
	log_assert(0);
}