static inline unsigned long do_div_llr(const long long dividend,
				       const long divisor, long *remainder)
{
	u64 result = dividend;

	*(remainder) = do_div(result, divisor);
	return (unsigned long) result;
}