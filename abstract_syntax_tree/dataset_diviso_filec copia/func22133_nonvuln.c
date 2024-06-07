static inline unsigned int lpf_count_to_ns(unsigned int count)
{
	
	return DIV_ROUND_CLOSEST(count * 1000,
				 CX23888_IR_REFCLK_FREQ / 1000000);
}