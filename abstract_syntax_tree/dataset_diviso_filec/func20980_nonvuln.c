
static JSValue js_file_getc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
	char res[2];
	FILE *f = JS_GetOpaque(this_val, file_class_id);
	if (!f) return GF_JS_EXCEPTION(ctx);

	res[0] = gf_fgetc(f);
	res[1] = 0;
	return JS_NewString(ctx, res);