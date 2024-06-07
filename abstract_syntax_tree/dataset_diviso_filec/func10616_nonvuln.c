
static void js_fileio_gc_mark(JSRuntime *rt, JSValueConst this_val, JS_MarkFunc *mark_func)
{
	JSFileIOCtx *ioctx = JS_GetOpaque(this_val, fileio_class_id);
	if (!ioctx) return;
	if (ioctx->factory->root == ioctx) {
		JSFileIOFactoryCtx *iofac = ioctx->factory;
		JS_MarkValue(rt, iofac->open, mark_func);
		JS_MarkValue(rt, iofac->close, mark_func);
		JS_MarkValue(rt, iofac->write, mark_func);
		JS_MarkValue(rt, iofac->read, mark_func);
		JS_MarkValue(rt, iofac->tell, mark_func);
		JS_MarkValue(rt, iofac->seek, mark_func);
		JS_MarkValue(rt, iofac->eof, mark_func);
		JS_MarkValue(rt, iofac->exists, mark_func);
		JS_MarkValue(rt, iofac->factory_obj, mark_func);
	}
	JS_MarkValue(rt, ioctx->js_obj, mark_func);