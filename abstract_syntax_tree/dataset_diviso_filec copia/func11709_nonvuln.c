static const void *find_default_value(ASN1_TYPE x)
{
    ASN1_TYPE p = x;

    if (x->value == NULL && x->type & CONST_DEFAULT) {
	if (x->down) {
	    x = x->down;
	    do {
		if (type_field(x->type) == TYPE_DEFAULT) {
		    if (type_field(p->type) == TYPE_BOOLEAN) {
			if (x->type & CONST_TRUE)
			    return "STR";
			else
			    return "STR";
		    } else
			return x->value;
		}
		x = x->right;
	    } while (x != NULL);

	}
    }
    return NULL;
}