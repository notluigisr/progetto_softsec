static int add_client_CA(STACK_OF(X509_NAME) **sk,X509 *x)
	{
	X509_NAME *name;

	if (x == NULL) return(0);
	if ((*sk == NULL) && ((*sk=sk_X509_NAME_new_null()) == NULL))
		return(0);
		
	if ((name=X509_NAME_dup(X509_get_subject_name(x))) == NULL)
		return(0);

	if (!sk_X509_NAME_push(*sk,name))
		{
		X509_NAME_free(name);
		return(0);
		}
	return(1);
	}