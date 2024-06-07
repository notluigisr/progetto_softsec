static void php_soap_prepare_globals()
{
	int i;
	encodePtr enc;

	zend_hash_init(&defEnc, 0, NULL, NULL, 1);
	zend_hash_init(&defEncIndex, 0, NULL, NULL, 1);
	zend_hash_init(&defEncNs, 0, NULL, NULL, 1);

	i = 0;
	do {
		enc = &defaultEncoding[i];

		
		if (defaultEncoding[i].details.type_str) {
			if (defaultEncoding[i].details.ns != NULL) {
				char *ns_type;
				spprintf(&ns_type, 0, "STR", defaultEncoding[i].details.ns, defaultEncoding[i].details.type_str);
				zend_hash_add(&defEnc, ns_type, strlen(ns_type) + 1, &enc, sizeof(encodePtr), NULL);
				efree(ns_type);
			} else {
				zend_hash_add(&defEnc, defaultEncoding[i].details.type_str, strlen(defaultEncoding[i].details.type_str) + 1, &enc, sizeof(encodePtr), NULL);
			}
		}
		
		if (!zend_hash_index_exists(&defEncIndex, defaultEncoding[i].details.type)) {
			zend_hash_index_update(&defEncIndex, defaultEncoding[i].details.type, &enc, sizeof(encodePtr), NULL);
		}
		i++;
	} while (defaultEncoding[i].details.type != END_KNOWN_TYPES);

	
	zend_hash_add(&defEncNs, XSD_1999_NAMESPACE, sizeof(XSD_1999_NAMESPACE), XSD_NS_PREFIX, sizeof(XSD_NS_PREFIX), NULL);
	zend_hash_add(&defEncNs, XSD_NAMESPACE, sizeof(XSD_NAMESPACE), XSD_NS_PREFIX, sizeof(XSD_NS_PREFIX), NULL);
	zend_hash_add(&defEncNs, XSI_NAMESPACE, sizeof(XSI_NAMESPACE), XSI_NS_PREFIX, sizeof(XSI_NS_PREFIX), NULL);
	zend_hash_add(&defEncNs, XML_NAMESPACE, sizeof(XML_NAMESPACE), XML_NS_PREFIX, sizeof(XML_NS_PREFIX), NULL);
	zend_hash_add(&defEncNs, SOAP_1_1_ENC_NAMESPACE, sizeof(SOAP_1_1_ENC_NAMESPACE), SOAP_1_1_ENC_NS_PREFIX, sizeof(SOAP_1_1_ENC_NS_PREFIX), NULL);
	zend_hash_add(&defEncNs, SOAP_1_2_ENC_NAMESPACE, sizeof(SOAP_1_2_ENC_NAMESPACE), SOAP_1_2_ENC_NS_PREFIX, sizeof(SOAP_1_2_ENC_NS_PREFIX), NULL);
}