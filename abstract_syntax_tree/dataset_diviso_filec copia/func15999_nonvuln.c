static void context_run(struct context *ctx, u32 extra)
{
	struct fw_ohci *ohci = ctx->ohci;

	reg_write(ohci, COMMAND_PTR(ctx->regs),
		  le32_to_cpu(ctx->last->branch_address));
	reg_write(ohci, CONTROL_CLEAR(ctx->regs), ~0);
	reg_write(ohci, CONTROL_SET(ctx->regs), CONTEXT_RUN | extra);
	flush_writes(ohci);
}