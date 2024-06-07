mono_type_create_fnptr_from_mono_method (VerifyContext *ctx, MonoMethod *method)
{
	MonoType *res = g_new0 (MonoType, 1);
	
	res->data.method = mono_method_signature (method);
	res->type = MONO_TYPE_FNPTR;
	ctx->funptrs = g_slist_prepend (ctx->funptrs, res);
	return res;
}