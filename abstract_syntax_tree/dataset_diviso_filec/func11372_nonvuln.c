sasl_session_abort(struct sasl_session *const restrict p)
{
	(void) sasl_sts(p->uid, 'D', "STR");
	(void) sasl_session_destroy(p);
}