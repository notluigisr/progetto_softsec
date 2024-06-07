e_mail_formatter_format_security_header (EMailFormatter *formatter,
                                         EMailFormatterContext *context,
                                         GString *buffer,
                                         EMailPart *part,
                                         guint32 flags)
{
	const gchar* part_id;
	gchar* part_id_prefix;
	GString* tmp;
	GQueue queue = G_QUEUE_INIT;
	GList *head, *link;

	g_return_if_fail (E_IS_MAIL_PART_HEADERS (part));

	
	part_id = e_mail_part_get_id (part);
	part_id_prefix = g_strndup (part_id, g_strrstr (part_id, "STR") - part_id);

	
	tmp = g_string_new ("");

	e_mail_part_list_queue_parts (context->part_list, NULL, &queue);

	head = g_queue_peek_head_link (&queue);

	
	for (link = head; link != NULL; link = g_list_next(link)) {
		EMailPart *mail_part = link->data;

		if (!e_mail_part_has_validity (mail_part))
			continue;

		if (!e_mail_part_id_has_prefix (mail_part, part_id_prefix))
			continue;

		if (e_mail_part_get_validity (mail_part, E_MAIL_PART_VALIDITY_PGP | E_MAIL_PART_VALIDITY_SIGNED)) {
			g_string_append (tmp, _("STR"));
		}

		if (e_mail_part_get_validity (mail_part, E_MAIL_PART_VALIDITY_PGP | E_MAIL_PART_VALIDITY_ENCRYPTED)) {
			if (tmp->len > 0)
				g_string_append (tmp, "STR");
			g_string_append (tmp, _("STR"));
		}

		if (e_mail_part_get_validity (mail_part, E_MAIL_PART_VALIDITY_SMIME | E_MAIL_PART_VALIDITY_SIGNED)) {
			if (tmp->len > 0)
				g_string_append (tmp, "STR");
			g_string_append (tmp, _("STR"));
		}

		if (e_mail_part_get_validity (mail_part, E_MAIL_PART_VALIDITY_SMIME | E_MAIL_PART_VALIDITY_ENCRYPTED)) {
			if (tmp->len > 0)
				g_string_append (tmp, "STR");
			g_string_append (tmp, _("STR"));
		}

		break;
	}

	if (tmp->len > 0) {
		e_mail_formatter_format_header (
			formatter, buffer,
			_("STR"), tmp->str,
			flags,
			"STR");
	}

	while (!g_queue_is_empty (&queue))
		g_object_unref (g_queue_pop_head (&queue));

	g_string_free (tmp, TRUE);
	g_free (part_id_prefix);
}