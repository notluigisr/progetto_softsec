static inline u32 tcp_cookie_time(void)
{
	struct timespec now;
	getnstimeofday(&now);
	return now.tv_sec >> 6; 
}