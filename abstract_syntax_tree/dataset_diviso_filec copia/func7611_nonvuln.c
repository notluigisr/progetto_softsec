do_stelem (VerifyContext *ctx, int opcode, int token)
{
	ILStackDesc *index, *array, *value;
	MonoType *type;
	if (!check_underflow (ctx, 3))
		return;

	if (opcode == CEE_STELEM) {
		if (!(type = verifier_load_type (ctx, token, "STR"))) {
			ADD_VERIFY_ERROR (ctx, g_strdup_printf ("STR", token, ctx->ip_offset));
			return;
		}
	} else {
		type = mono_type_from_opcode (opcode);
	}
	
	value = stack_pop (ctx);
	index = stack_pop (ctx);
	array = stack_pop (ctx);

	if (stack_slot_get_type (index) != TYPE_I4 && stack_slot_get_type (index) != TYPE_NATIVE_INT)
		CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("STR", stack_slot_get_name (index), ctx->ip_offset));

	if (!stack_slot_is_null_literal (array)) {
		if (stack_slot_get_type (array) != TYPE_COMPLEX || array->type->type != MONO_TYPE_SZARRAY) {
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("STR", stack_slot_get_name (array), ctx->ip_offset));
		} else {
			if (opcode == CEE_STELEM_REF) {
				if (array->type->data.klass->valuetype)
					CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("STR", ctx->ip_offset));
			} else if (!verify_type_compatibility_full (ctx, &array->type->data.klass->byval_arg, type, TRUE)) {
					CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("STR", ctx->ip_offset));
			}
		}
	}
	if (opcode == CEE_STELEM_REF) {
		if (!stack_slot_is_boxed_value (value) && mono_class_from_mono_type (value->type)->valuetype)
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("STR", ctx->ip_offset));
	} else if (opcode != CEE_STELEM_REF) {
		if (!verify_stack_type_compatibility (ctx, type, value))
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("STR", ctx->ip_offset));

		if (stack_slot_is_boxed_value (value) && !MONO_TYPE_IS_REFERENCE (value->type) && !MONO_TYPE_IS_REFERENCE (type))
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("STR", ctx->ip_offset));

	}
}