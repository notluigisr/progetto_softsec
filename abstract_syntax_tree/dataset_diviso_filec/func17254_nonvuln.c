pkcs11dsa_compare(const dst_key_t *key1, const dst_key_t *key2) {
	pk11_object_t *dsa1, *dsa2;
	CK_ATTRIBUTE *attr1, *attr2;

	dsa1 = key1->keydata.pkey;
	dsa2 = key2->keydata.pkey;

	if ((dsa1 == NULL) && (dsa2 == NULL))
		return (true);
	else if ((dsa1 == NULL) || (dsa2 == NULL))
		return (false);

	attr1 = pk11_attribute_bytype(dsa1, CKA_PRIME);
	attr2 = pk11_attribute_bytype(dsa2, CKA_PRIME);
	if ((attr1 == NULL) && (attr2 == NULL))
		return (true);
	else if ((attr1 == NULL) || (attr2 == NULL) ||
		 (attr1->ulValueLen != attr2->ulValueLen) ||
		 !isc_safe_memequal(attr1->pValue, attr2->pValue,
				    attr1->ulValueLen))
		return (false);

	attr1 = pk11_attribute_bytype(dsa1, CKA_SUBPRIME);
	attr2 = pk11_attribute_bytype(dsa2, CKA_SUBPRIME);
	if ((attr1 == NULL) && (attr2 == NULL))
		return (true);
	else if ((attr1 == NULL) || (attr2 == NULL) ||
		 (attr1->ulValueLen != attr2->ulValueLen) ||
		 !isc_safe_memequal(attr1->pValue, attr2->pValue,
				    attr1->ulValueLen))
		return (false);

	attr1 = pk11_attribute_bytype(dsa1, CKA_BASE);
	attr2 = pk11_attribute_bytype(dsa2, CKA_BASE);
	if ((attr1 == NULL) && (attr2 == NULL))
		return (true);
	else if ((attr1 == NULL) || (attr2 == NULL) ||
		 (attr1->ulValueLen != attr2->ulValueLen) ||
		 !isc_safe_memequal(attr1->pValue, attr2->pValue,
				    attr1->ulValueLen))
		return (false);

	attr1 = pk11_attribute_bytype(dsa1, CKA_VALUE);
	attr2 = pk11_attribute_bytype(dsa2, CKA_VALUE);
	if ((attr1 == NULL) && (attr2 == NULL))
		return (true);
	else if ((attr1 == NULL) || (attr2 == NULL) ||
		 (attr1->ulValueLen != attr2->ulValueLen) ||
		 !isc_safe_memequal(attr1->pValue, attr2->pValue,
				    attr1->ulValueLen))
		return (false);

	attr1 = pk11_attribute_bytype(dsa1, CKA_VALUE2);
	attr2 = pk11_attribute_bytype(dsa2, CKA_VALUE2);
	if (((attr1 != NULL) || (attr2 != NULL)) &&
	    ((attr1 == NULL) || (attr2 == NULL) ||
	     (attr1->ulValueLen != attr2->ulValueLen) ||
	     !isc_safe_memequal(attr1->pValue, attr2->pValue,
				attr1->ulValueLen)))
		return (false);

	if (!dsa1->ontoken && !dsa2->ontoken)
		return (true);
	else if (dsa1->ontoken || dsa2->ontoken ||
		 (dsa1->object != dsa2->object))
		return (false);

	return (true);
}