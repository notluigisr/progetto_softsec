static int __init serial_ir_init_module(void)
{
	int result;

	switch (type) {
	case IR_HOMEBREW:
	case IR_IRDEO:
	case IR_IRDEO_REMOTE:
	case IR_ANIMAX:
	case IR_IGOR:
		
		io = io ? io : 0x3f8;
		irq = irq ? irq : 4;
		break;
	default:
		return -EINVAL;
	}
	if (!softcarrier) {
		switch (type) {
		case IR_HOMEBREW:
		case IR_IGOR:
			hardware[type].set_send_carrier = false;
			hardware[type].set_duty_cycle = false;
			break;
		}
	}

	
	if (sense != -1)
		sense = !!sense;

	result = serial_ir_init();
	if (!result)
		return 0;

	serial_ir_exit();
	return result;
}