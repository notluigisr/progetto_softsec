eog_image_load_error_message_area_new (const gchar  *caption,
				       const GError *error)
{
	GtkWidget *message_area;
	gchar *error_message = NULL;
	gchar *message_details = NULL;
	gchar *pango_escaped_caption = NULL;

	g_return_val_if_fail (caption != NULL, NULL);
	g_return_val_if_fail (error != NULL, NULL);

	
	pango_escaped_caption = g_markup_escape_text (caption, -1);
	error_message = g_strdup_printf (_("STR"),
					 pango_escaped_caption);

	message_details = g_strdup (error->message);

	message_area = create_error_message_area (error_message,
						  message_details,
						  EOG_ERROR_MESSAGE_AREA_CANCEL_BUTTON);

	g_free (pango_escaped_caption);
	g_free (error_message);
	g_free (message_details);

	return message_area;
}