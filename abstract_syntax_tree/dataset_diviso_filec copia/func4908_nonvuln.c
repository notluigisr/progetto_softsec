static void vmx_free_vcpu(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	free_vpid(vmx);
	free_nested(vmx);
	free_loaded_vmcs(vmx->loaded_vmcs);
	kfree(vmx->guest_msrs);
	kvm_vcpu_uninit(vcpu);
	kmem_cache_free(kvm_vcpu_cache, vmx);
}