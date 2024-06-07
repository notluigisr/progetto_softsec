
static int js_gpaccore_init(JSContext *ctx, JSModuleDef *m)
{
	JSValue proto, ctor;
	if (!bitstream_class_id) {
		JS_NewClassID(&bitstream_class_id);
		JS_NewClass(JS_GetRuntime(ctx), bitstream_class_id, &bitstreamClass);

		JS_NewClassID(&sha1_class_id);
		JS_NewClass(JS_GetRuntime(ctx), sha1_class_id, &sha1Class);

		JS_NewClassID(&file_class_id);
		JS_NewClass(JS_GetRuntime(ctx), file_class_id, &fileClass);

		JS_NewClassID(&amix_class_id);
		JS_NewClass(JS_GetRuntime(ctx), amix_class_id, &amixClass);

		JS_NewClassID(&fileio_class_id);
		JS_NewClass(JS_GetRuntime(ctx), fileio_class_id, &fileioClass);
	}

	JSValue core_o = JS_NewObject(ctx);
	JS_SetPropertyFunctionList(ctx, core_o, sys_funcs, countof(sys_funcs));
    JS_SetModuleExport(ctx, m, "STR", core_o);

	JSValue args = JS_NewArray(ctx);
    u32 i, nb_args = gf_sys_get_argc();
    for (i=0; i<nb_args; i++) {
        JS_SetPropertyUint32(ctx, args, i, JS_NewString(ctx, gf_sys_get_arg(i)));
    }
    JS_SetPropertyStr(ctx, core_o, "STR", args);


    JS_SetPropertyStr(ctx, core_o, #_val, JS_NewInt32(ctx, _val));

	DEF_CONST(GF_CONSOLE_RESET)
	DEF_CONST(GF_CONSOLE_RED)
	DEF_CONST(GF_CONSOLE_GREEN)
	DEF_CONST(GF_CONSOLE_BLUE)
	DEF_CONST(GF_CONSOLE_YELLOW)
	DEF_CONST(GF_CONSOLE_CYAN)
	DEF_CONST(GF_CONSOLE_WHITE)
	DEF_CONST(GF_CONSOLE_MAGENTA)
	DEF_CONST(GF_CONSOLE_CLEAR)
	DEF_CONST(GF_CONSOLE_SAVE)
	DEF_CONST(GF_CONSOLE_RESTORE)
	DEF_CONST(GF_CONSOLE_BOLD)
	DEF_CONST(GF_CONSOLE_ITALIC)
	DEF_CONST(GF_CONSOLE_UNDERLINED)
	DEF_CONST(GF_CONSOLE_STRIKE)
	DEF_CONST(SEEK_SET)
	DEF_CONST(SEEK_CUR)
	DEF_CONST(SEEK_END)

#undef DEF_CONST


	
	proto = JS_NewObjectClass(ctx, bitstream_class_id);
	JS_SetPropertyFunctionList(ctx, proto, bitstream_funcs, countof(bitstream_funcs));
	JS_SetClassProto(ctx, bitstream_class_id, proto);
	ctor = JS_NewCFunction2(ctx, bitstream_constructor, "STR", 1, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "STR", ctor);

	
	proto = JS_NewObjectClass(ctx, sha1_class_id);
	JS_SetPropertyFunctionList(ctx, proto, sha1_funcs, countof(sha1_funcs));
	JS_SetClassProto(ctx, sha1_class_id, proto);
	ctor = JS_NewCFunction2(ctx, sha1_constructor, "STR", 1, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "STR", ctor);

	
	proto = JS_NewObjectClass(ctx, file_class_id);
	JS_SetPropertyFunctionList(ctx, proto, file_funcs, countof(file_funcs));
	JS_SetClassProto(ctx, file_class_id, proto);
	ctor = JS_NewCFunction2(ctx, file_constructor, "STR", 1, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "STR", ctor);

	
	proto = JS_NewObjectClass(ctx, amix_class_id);
	JS_SetPropertyFunctionList(ctx, proto, amix_funcs, countof(amix_funcs));
	JS_SetClassProto(ctx, amix_class_id, proto);
	ctor = JS_NewCFunction2(ctx, amix_constructor, "STR", 1, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "STR", ctor);

	
	proto = JS_NewObjectClass(ctx, fileio_class_id);
	JS_SetPropertyFunctionList(ctx, proto, fileio_funcs, countof(fileio_funcs));
	JS_SetClassProto(ctx, fileio_class_id, proto);
	ctor = JS_NewCFunction2(ctx, fileio_constructor, "STR", 1, JS_CFUNC_constructor, 0);
    JS_SetModuleExport(ctx, m, "STR", ctor);

	return 0;