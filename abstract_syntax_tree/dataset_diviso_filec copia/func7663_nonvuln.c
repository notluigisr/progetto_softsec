find_book_view (EBookBackendLDAP *bl)
{
	EDataBookView *view = NULL;
	GList *list;

	list = e_book_backend_list_views (E_BOOK_BACKEND (bl));

	if (list != NULL) {
		
		view = E_DATA_BOOK_VIEW (list->data);
		g_list_free_full (list, (GDestroyNotify) g_object_unref);
	}

	return view;
}