static int FNAME(cmpxchg_gpte)(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu,
			       pt_element_t __user *ptep_user, unsigned index,
			       pt_element_t orig_pte, pt_element_t new_pte)
{
	signed char r;

	if (!user_access_begin(ptep_user, sizeof(pt_element_t)))
		return -EFAULT;

#ifdef CMPXCHG
	asm volatile("STR"
		     "STR"
		     "STR"
		     _ASM_EXTABLE_TYPE_REG(1b, 2b, EX_TYPE_EFAULT_REG, %k[r])
		     : [ptr] "STR" (*ptep_user),
		       [old] "STR" (orig_pte),
		       [r] "STR" (r)
		     : [new] "STR" (new_pte)
		     : "STR");
#else
	asm volatile("STR"
		     "STR"
		     "STR"
		     _ASM_EXTABLE_TYPE_REG(1b, 2b, EX_TYPE_EFAULT_REG, %k[r])
		     : [ptr] "STR" (*ptep_user),
		       [old] "STR" (orig_pte),
		       [r] "STR" (r)
		     : [new_lo] "STR" ((u32)new_pte),
		       [new_hi] "STR" ((u32)(new_pte >> 32))
		     : "STR");
#endif

	user_access_end();
	return r;
}