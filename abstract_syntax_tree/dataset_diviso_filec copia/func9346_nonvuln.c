homephone_ber (EContact *contact)
{
	struct berval ** result;
	const gchar *homephones[3];
	gint i, j, num;

	num = 0;
	if ((homephones[0] = e_contact_get (contact, E_CONTACT_PHONE_HOME)))
		num++;
	if ((homephones[1] = e_contact_get (contact, E_CONTACT_PHONE_HOME_2)))
		num++;

	if (num == 0)
		return NULL;

	result = g_new (struct berval *, num + 1);

	for (i = 0; i < num; i++)
		result[i] = g_new (struct berval, 1);

	j = 0;
	for (i = 0; i < 2; i++) {
		if (homephones[i]) {
			result[j]->bv_val = g_strdup (homephones[i]);
			result[j++]->bv_len = strlen (homephones[i]);
		}
	}

	result[num] = NULL;

	return result;
}