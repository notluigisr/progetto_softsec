static void emulator_get_idt(struct x86_emulate_ctxt *ctxt, struct desc_ptr *dt)
{
	static_call(kvm_x86_get_idt)(emul_to_vcpu(ctxt), dt);
}