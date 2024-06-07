
static JSValue js_pixfmt_transparent(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
	GF_PropertyValue prop;
	if (!argc) return GF_JS_EXCEPTION(ctx);
	GF_Err e = jsf_ToProp_ex(NULL, ctx, argv[0], 0, &prop, GF_PROP_PIXFMT);
	if (e) return GF_JS_EXCEPTION(ctx);

	return JS_NewBool(ctx, 	gf_pixel_fmt_is_transparent(prop.value.uint) );