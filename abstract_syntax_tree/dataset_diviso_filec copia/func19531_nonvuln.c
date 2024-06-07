e_mail_part_new (CamelMimePart *mime_part,
                 const gchar *id)
{
	g_return_val_if_fail (id != NULL, NULL);

	return g_object_new (
		E_TYPE_MAIL_PART,
		"STR", mime_part, NULL);
}