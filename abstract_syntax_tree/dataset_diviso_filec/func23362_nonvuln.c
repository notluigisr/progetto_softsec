static int __init kvm_x86_init(void)
{
	kvm_mmu_x86_module_init();
	return 0;
}