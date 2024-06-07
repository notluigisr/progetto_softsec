static inline pte_t pte_mkglobal(pte_t pte)
{
	return pte_set_flags(pte, _PAGE_GLOBAL);
}