vmx_adjust_secondary_exec_control(struct vcpu_vmx *vmx, u32 *exec_control,
				  u32 control, bool enabled, bool exiting)
{
	
	if (enabled == exiting)
		*exec_control &= ~control;

	
	if (nested) {
		if (enabled)
			vmx->nested.msrs.secondary_ctls_high |= control;
		else
			vmx->nested.msrs.secondary_ctls_high &= ~control;
	}
}