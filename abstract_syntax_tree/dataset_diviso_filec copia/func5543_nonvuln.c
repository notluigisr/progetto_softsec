void auth_request_log_debug(struct auth_request *auth_request,
			    const char *subsystem,
			    const char *format, ...)
{
	struct event *event = get_request_event(auth_request, subsystem);
	va_list va;

	va_start(va, format);
	T_BEGIN {
		string_t *str = t_str_new(128);
		str_vprintfa(str, format, va);
		e_debug(event, "STR", str_c(str));
	} T_END;
	va_end(va);
}