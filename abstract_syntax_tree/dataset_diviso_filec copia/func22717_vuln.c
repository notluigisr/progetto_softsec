static inline long div_long_long_rem_signed(const long long dividend,
					    const long divisor, long *remainder)
{
	long res;

	if (unlikely(dividend < 0)) {
		res = -div_long_long_rem(-dividend, divisor, remainder);
		*remainder = -(*remainder);
	} else
		res = div_long_long_rem(dividend, divisor, remainder);

	return res;
}