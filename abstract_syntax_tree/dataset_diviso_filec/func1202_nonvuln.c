static void sdl_deserialize_attribute(sdlAttributePtr attr, encodePtr *encoders, char **in)
{
	int i;

	attr->name = sdl_deserialize_string(in);
	attr->namens = sdl_deserialize_string(in);
	attr->ref = sdl_deserialize_string(in);
	attr->def = sdl_deserialize_string(in);
	attr->fixed = sdl_deserialize_string(in);
	WSDL_CACHE_GET_1(attr->form, sdlForm, in);
	WSDL_CACHE_GET_1(attr->use, sdlUse, in);
	WSDL_CACHE_GET_INT(i, in);
	attr->encode = encoders[i];
	WSDL_CACHE_GET_INT(i, in);
	if (i > 0) {
		attr->extraAttributes = emalloc(sizeof(HashTable));
		zend_hash_init(attr->extraAttributes, i, NULL, delete_extra_attribute, 0);
		while (i > 0) {
			sdlExtraAttributePtr x = emalloc(sizeof(sdlExtraAttribute));
			sdl_deserialize_key(attr->extraAttributes, x, in);
			x->ns = sdl_deserialize_string(in);
			x->val = sdl_deserialize_string(in);
			--i;
		}
	}
}