static JSValue js_sys_getenv(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
	const char *str, *val;
	if (!argc) return GF_JS_EXCEPTION(ctx);
	str = JS_ToCString(ctx, argv[0]);
	if (!str) return GF_JS_EXCEPTION(ctx);
	val = getenv(str);
	JS_FreeCString(ctx, str);
	return val ? JS_NewString(ctx, val) : JS_NULL;
}