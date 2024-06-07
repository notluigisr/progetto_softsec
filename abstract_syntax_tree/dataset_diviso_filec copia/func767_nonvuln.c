ebb_ews_server_notification_cb (EBookBackendEws *bbews,
				const GSList *events,
				EEwsConnection *cnc)
{
	GSList *link;
	gboolean update_folder = FALSE;

	g_return_if_fail (E_IS_BOOK_BACKEND_EWS (bbews));

	for (link = (GSList *) events; link && !update_folder; link = g_slist_next (link)) {
		EEwsNotificationEvent *event = link->data;

		switch (event->type) {
			case E_EWS_NOTIFICATION_EVENT_CREATED:
			case E_EWS_NOTIFICATION_EVENT_DELETED:
			case E_EWS_NOTIFICATION_EVENT_MODIFIED:
				g_rec_mutex_lock (&bbews->priv->cnc_lock);

				if (g_strcmp0 (event->folder_id, bbews->priv->folder_id) == 0)
					update_folder = TRUE;

				g_rec_mutex_unlock (&bbews->priv->cnc_lock);
				break;
			case E_EWS_NOTIFICATION_EVENT_MOVED:
			case E_EWS_NOTIFICATION_EVENT_COPIED:
				g_rec_mutex_lock (&bbews->priv->cnc_lock);

				if (g_strcmp0 (event->folder_id, bbews->priv->folder_id) == 0 ||
				    g_strcmp0 (event->old_folder_id, bbews->priv->folder_id) == 0)
					update_folder = TRUE;

				g_rec_mutex_unlock (&bbews->priv->cnc_lock);
				break;
			default:
				return;
		}
	}

	if (update_folder)
		e_book_meta_backend_schedule_refresh (E_BOOK_META_BACKEND (bbews));
}