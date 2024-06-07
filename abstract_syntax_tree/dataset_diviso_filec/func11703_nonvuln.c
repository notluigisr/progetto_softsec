static int svm_enter_smm(struct kvm_vcpu *vcpu, char *smstate)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct kvm_host_map map_save;
	int ret;

	if (is_guest_mode(vcpu)) {
		
		put_smstate(u64, smstate, 0x7ed8, 1);
		
		put_smstate(u64, smstate, 0x7ee0, svm->nested.vmcb12_gpa);

		svm->vmcb->save.rax = vcpu->arch.regs[VCPU_REGS_RAX];
		svm->vmcb->save.rsp = vcpu->arch.regs[VCPU_REGS_RSP];
		svm->vmcb->save.rip = vcpu->arch.regs[VCPU_REGS_RIP];

		ret = nested_svm_vmexit(svm);
		if (ret)
			return ret;

		
		if (kvm_vcpu_map(vcpu, gpa_to_gfn(svm->nested.hsave_msr),
				 &map_save) == -EINVAL)
			return 1;

		BUILD_BUG_ON(offsetof(struct vmcb, save) != 0x400);

		svm_copy_vmrun_state(map_save.hva + 0x400,
				     &svm->vmcb01.ptr->save);

		kvm_vcpu_unmap(vcpu, &map_save, true);
	}
	return 0;
}