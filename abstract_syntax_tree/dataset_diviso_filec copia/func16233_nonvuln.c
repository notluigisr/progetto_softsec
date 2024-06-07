static inline int cap_limit_ptraced_target(void)
{
	return !capable(CAP_SETPCAP);
}