static bool valid_mtrr_type(unsigned t)
{
	return t < 8 && (1 << t) & 0x73; 
}