static int java_cmd_ext(RAnal *anal, const char* input) {
	RBinJavaObj *obj = (RBinJavaObj *) get_java_bin_obj (anal);

	if (!obj) {
		eprintf ("STR");
		return -1;
	}
	switch (*input) {
	case 'c':
		
		r_java_new_method ();
		break;
	case 'u':
		switch (*(input+1)) {
			case 't': {java_update_anal_types (anal, obj); return true;}
			default: break;
		}
		break;
	case 's':
		switch (*(input+1)) {
			
			default: break;
		}
		break;

	default: eprintf("STR"); break;
	}
	return 0;
}