static int em_lldt(struct x86_emulate_ctxt *ctxt)
{
	u16 sel = ctxt->src.val;

	
	ctxt->dst.type = OP_NONE;
	return load_segment_descriptor(ctxt, sel, VCPU_SREG_LDTR);
}