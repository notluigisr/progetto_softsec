static inline bool allow_unknown_peers(void) {
	return ctx.has_floating || fastd_allow_verify();
}