static inline int emulate_grp45(struct x86_emulate_ctxt *ctxt,
			       struct x86_emulate_ops *ops)
{
	struct decode_cache *c = &ctxt->decode;

	switch (c->modrm_reg) {
	case 0:	
		emulate_1op("STR", c->dst, ctxt->eflags);
		break;
	case 1:	
		emulate_1op("STR", c->dst, ctxt->eflags);
		break;
	case 2:  {
		long int old_eip;
		old_eip = c->eip;
		c->eip = c->src.val;
		c->src.val = old_eip;
		emulate_push(ctxt);
		break;
	}
	case 4: 
		c->eip = c->src.val;
		break;
	case 6:	
		emulate_push(ctxt);
		break;
	}
	return 0;
}