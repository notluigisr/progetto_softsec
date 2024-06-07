static HashTable* make_persistent_sdl_function_faults(sdlFunctionPtr func, HashTable *faults, HashTable *ptr_map)
{
	HashTable *pfaults;
	sdlFaultPtr tmp, pfault;
	zend_string *key;

	pfaults = malloc(sizeof(HashTable));
	zend_hash_init(pfaults, zend_hash_num_elements(faults), NULL, delete_fault_persistent, 1);

	ZEND_HASH_FOREACH_STR_KEY_PTR(faults, key, tmp) {
		pfault = malloc(sizeof(sdlFault));
		memset(pfault, 0, sizeof(sdlFault));
		*pfault = *tmp;

		if (pfault->name) {
			pfault->name = strdup(pfault->name);
		}
		if (pfault->details) {
			pfault->details = make_persistent_sdl_parameters(pfault->details, ptr_map);
		}

		if (func->binding->bindingType == BINDING_SOAP && pfault->bindingAttributes) {
			sdlSoapBindingFunctionFaultPtr soap_binding;

		   	soap_binding = malloc(sizeof(sdlSoapBindingFunctionFault));
			memset(soap_binding, 0, sizeof(sdlSoapBindingFunctionFault));
			*soap_binding = *(sdlSoapBindingFunctionFaultPtr)pfault->bindingAttributes;
			if (soap_binding->ns) {
				soap_binding->ns = strdup(soap_binding->ns);
			}
			pfault->bindingAttributes = soap_binding;
		}

		if (key) {
			
			zend_hash_str_add_ptr(pfaults, ZSTR_VAL(key), ZSTR_LEN(key), pfault);
		} else {
			zend_hash_next_index_insert_ptr(pfaults, pfault);
		}

	} ZEND_HASH_FOREACH_END();

	return pfaults;
}