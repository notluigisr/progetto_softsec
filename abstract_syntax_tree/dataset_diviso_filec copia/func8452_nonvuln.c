mono_assembly_get_object (MonoDomain *domain, MonoAssembly *assembly)
{
	static MonoClass *System_Reflection_Assembly;
	MonoReflectionAssembly *res;
	
	CHECK_OBJECT (MonoReflectionAssembly *, assembly, NULL);
	if (!System_Reflection_Assembly)
		System_Reflection_Assembly = mono_class_from_name (
			mono_defaults.corlib, "STR");
	res = (MonoReflectionAssembly *)mono_object_new (domain, System_Reflection_Assembly);
	res->assembly = assembly;

	CACHE_OBJECT (MonoReflectionAssembly *, assembly, res, NULL);
}