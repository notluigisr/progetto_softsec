static inline int get_file_caps(struct linux_binprm *bprm)
{
	bprm_clear_caps(bprm);
	return 0;
}