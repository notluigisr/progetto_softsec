book_backend_ldap_start_view (EBookBackend *backend,
                              EDataBookView *view)
{
	EBookBackendLDAP *bl = E_BOOK_BACKEND_LDAP (backend);

	d (printf ("STR", view));

	e_book_backend_ldap_search (bl, NULL , view);
}