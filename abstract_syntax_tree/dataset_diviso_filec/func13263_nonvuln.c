e_mail_part_id_has_prefix (EMailPart *part,
                           const gchar *prefix)
{
	g_return_val_if_fail (E_IS_MAIL_PART (part), FALSE);
	g_return_val_if_fail (prefix != NULL, FALSE);

	return g_str_has_prefix (part->priv->id, prefix);
}