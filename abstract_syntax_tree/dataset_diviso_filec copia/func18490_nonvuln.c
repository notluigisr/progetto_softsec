static int gp_interception(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	u32 error_code = svm->vmcb->control.exit_info_1;
	int opcode;

	
	if (error_code)
		goto reinject;

	
	if (x86_decode_emulated_instruction(vcpu, 0, NULL, 0) != EMULATION_OK)
		goto reinject;

	opcode = svm_instr_opcode(vcpu);

	if (opcode == NONE_SVM_INSTR) {
		if (!enable_vmware_backdoor)
			goto reinject;

		
		if (!is_guest_mode(vcpu))
			return kvm_emulate_instruction(vcpu,
				EMULTYPE_VMWARE_GP | EMULTYPE_NO_DECODE);
	} else
		return emulate_svm_instr(vcpu, opcode);

reinject:
	kvm_queue_exception_e(vcpu, GP_VECTOR, error_code);
	return 1;
}