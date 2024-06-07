static inline int calc_idx(int idx, int rx_dlc)
{
	if (idx < 0)
		return rx_dlc + idx;
	else
		return idx;
}