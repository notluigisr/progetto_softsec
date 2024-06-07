get_contact_dtor (LDAPOp *op)
{
	LDAPGetContactOp *get_contact_op = (LDAPGetContactOp *) op;

	g_free (get_contact_op);
}