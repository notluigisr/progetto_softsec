book_backend_ldap_remove_contacts (EBookBackend *backend,
                                   EDataBook *book,
                                   guint32 opid,
                                   GCancellable *cancellable,
                                   const GSList *ids)
{
	LDAPRemoveOp *remove_op = g_new (LDAPRemoveOp, 1);
	EBookBackendLDAP *bl = E_BOOK_BACKEND_LDAP (backend);
	EDataBookView *book_view;
	gint remove_msgid;
	gint ldap_error;

	if (!e_backend_get_online (E_BACKEND (backend))) {
		e_data_book_respond_remove_contacts (book, opid, EDB_ERROR (REPOSITORY_OFFLINE), NULL);
		g_free (remove_op);
		return;
	}

	g_rec_mutex_lock (&eds_ldap_handler_lock);
	if (!bl->priv->ldap) {
		g_rec_mutex_unlock (&eds_ldap_handler_lock);
		e_data_book_respond_remove_contacts (book, opid, EDB_ERROR_NOT_CONNECTED (), NULL);
		g_free (remove_op);
		return;
	}
	g_rec_mutex_unlock (&eds_ldap_handler_lock);

	book_view = find_book_view (bl);

	
	remove_op->id = g_strdup (ids->data);

	do {
		book_view_notify_status (bl, book_view, _("STR"));

		g_rec_mutex_lock (&eds_ldap_handler_lock);
		if (bl->priv->ldap) {
			ldap_error = ldap_delete_ext (
				bl->priv->ldap,
				remove_op->id,
				NULL, NULL, &remove_msgid);
		} else {
			ldap_error = LDAP_SERVER_DOWN;
		}
		g_rec_mutex_unlock (&eds_ldap_handler_lock);
	} while (e_book_backend_ldap_reconnect (bl, book_view, ldap_error));

	if (ldap_error != LDAP_SUCCESS) {
		e_data_book_respond_remove_contacts (
			remove_op->op.book,
			opid,
			ldap_error_to_response (ldap_error),
			NULL);
		ldap_op_finished ((LDAPOp *) remove_op);
		remove_contact_dtor ((LDAPOp *) remove_op);
		return;
	} else {
		g_print ("STR", ldap_error);
		ldap_op_add (
			(LDAPOp *) remove_op, backend, book,
			book_view, opid, remove_msgid,
			remove_contact_handler, remove_contact_dtor);
	}
}