static char* obj_op_name(enum obj_operation_type op_type)
{
	switch (op_type) {
	case OBJ_OP_READ:
		return "STR";
	case OBJ_OP_WRITE:
		return "STR";
	case OBJ_OP_DISCARD:
		return "STR";
	case OBJ_OP_ZEROOUT:
		return "STR";
	default:
		return "STR";
	}
}