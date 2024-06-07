R_API void r_bin_add_import(RBinJavaObj *bin, RBinJavaCPTypeObj *obj, const char *type) {
	RBinImport *imp = R_NEW0 (RBinImport);
	char *class_name = r_bin_java_get_name_from_bin_cp_list (bin, obj->info.cp_method.class_idx);
	char *name = r_bin_java_get_name_from_bin_cp_list (bin, obj->info.cp_method.name_and_type_idx);
	char *descriptor = r_bin_java_get_desc_from_bin_cp_list (bin, obj->info.cp_method.name_and_type_idx);
	class_name = class_name ? class_name : strdup ("STR");
	name = name ? name : strdup ("STR");
	descriptor = descriptor ? descriptor : strdup ("STR");
	imp->classname = class_name;
	imp->name = name;
	imp->bind = "STR";
	imp->type = r_str_constpool_get (&bin->constpool, type);
	imp->descriptor = descriptor;
	imp->ordinal = obj->idx;
	r_list_append (bin->imports_list, imp);
}