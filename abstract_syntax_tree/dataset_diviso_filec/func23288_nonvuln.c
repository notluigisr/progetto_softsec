static inline u32 smca_status_reg(int bank)
{
	return MSR_AMD64_SMCA_MCx_STATUS(bank);
}