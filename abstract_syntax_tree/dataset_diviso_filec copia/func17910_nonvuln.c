static sdlRestrictionIntPtr sdl_deserialize_resriction_int(char **in)
{
	if (**in == 1) {
		sdlRestrictionIntPtr x = emalloc(sizeof(sdlRestrictionInt));
		WSDL_CACHE_SKIP(1, in);
		WSDL_CACHE_GET_INT(x->value, in);
		WSDL_CACHE_GET_1(x->fixed, char, in);
		return x;
	} else {
		WSDL_CACHE_SKIP(1, in);
		return NULL;
	}
}