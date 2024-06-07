static inline int pte_hidden(pte_t pte)
{
	return pte_flags(pte) & _PAGE_HIDDEN;
}