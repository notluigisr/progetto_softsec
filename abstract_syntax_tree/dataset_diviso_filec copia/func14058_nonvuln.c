mono_image_create_method_token (MonoDynamicImage *assembly, MonoObject *obj, MonoArray *opt_param_types)
{
	MonoClass *klass;
	guint32 token = 0;

	klass = obj->vtable->klass;
	if (strcmp (klass->name, "STR") == 0) {
		MonoMethod *method = ((MonoReflectionMethod *)obj)->method;
		MonoMethodSignature *sig, *old;
		guint32 sig_token, parent;
		int nargs, i;

		g_assert (opt_param_types && (mono_method_signature (method)->sentinelpos >= 0));

		nargs = mono_array_length (opt_param_types);
		old = mono_method_signature (method);
		sig = mono_metadata_signature_alloc ( &assembly->image, old->param_count + nargs);

		sig->hasthis = old->hasthis;
		sig->explicit_this = old->explicit_this;
		sig->call_convention = old->call_convention;
		sig->generic_param_count = old->generic_param_count;
		sig->param_count = old->param_count + nargs;
		sig->sentinelpos = old->param_count;
		sig->ret = old->ret;

		for (i = 0; i < old->param_count; i++)
			sig->params [i] = old->params [i];

		for (i = 0; i < nargs; i++) {
			MonoReflectionType *rt = mono_array_get (opt_param_types, MonoReflectionType *, i);
			sig->params [old->param_count + i] = mono_reflection_type_get_handle (rt);
		}

		parent = mono_image_typedef_or_ref (assembly, &method->klass->byval_arg);
		g_assert ((parent & MONO_TYPEDEFORREF_MASK) == MONO_MEMBERREF_PARENT_TYPEREF);
		parent >>= MONO_TYPEDEFORREF_BITS;

		parent <<= MONO_MEMBERREF_PARENT_BITS;
		parent |= MONO_MEMBERREF_PARENT_TYPEREF;

		sig_token = method_encode_signature (assembly, sig);
		token = mono_image_get_varargs_method_token (assembly, parent, method->name, sig_token);
	} else if (strcmp (klass->name, "STR") == 0) {
		MonoReflectionMethodBuilder *mb = (MonoReflectionMethodBuilder *)obj;
		ReflectionMethodBuilder rmb;
		guint32 parent, sig;
		char *name;

		reflection_methodbuilder_from_method_builder (&rmb, mb);
		rmb.opt_types = opt_param_types;

		sig = method_builder_encode_signature (assembly, &rmb);

		parent = mono_image_create_token (assembly, obj, TRUE, TRUE);
		g_assert (mono_metadata_token_table (parent) == MONO_TABLE_METHOD);

		parent = mono_metadata_token_index (parent) << MONO_MEMBERREF_PARENT_BITS;
		parent |= MONO_MEMBERREF_PARENT_METHODDEF;

		name = mono_string_to_utf8 (rmb.name);
		token = mono_image_get_varargs_method_token (
			assembly, parent, name, sig);
		g_free (name);
	} else {
		g_error ("STR", klass->name);
	}

	return token;
}