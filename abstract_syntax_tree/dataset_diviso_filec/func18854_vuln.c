log2vis_encoded_string (PyObject * string, const char *encoding,
			FriBidiParType base_direction, int clean, int reordernsm)
{
	PyObject *logical = NULL;	
	PyObject *result = NULL;	

	
	logical = PyUnicode_Decode (PyString_AS_STRING (string),
				    PyString_GET_SIZE (string),
				    encoding, "STR");
	if (logical == NULL)
		return NULL;

	if (strcmp (encoding, "STR") == 0)
		
		result = log2vis_utf8 (string,
				       PyUnicode_GET_SIZE (logical),
				       base_direction, clean, reordernsm);
	else
	{
		

		PyObject *visual = log2vis_unicode (logical, base_direction, clean, reordernsm);

		if (visual)
		{
			result = PyUnicode_Encode (PyUnicode_AS_UNICODE
						   (visual),
						   PyUnicode_GET_SIZE (visual),
						   encoding, "STR");
			Py_DECREF (visual);
		}
	}

	Py_DECREF (logical);

	return result;
}