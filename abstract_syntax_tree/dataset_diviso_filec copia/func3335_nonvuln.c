home_zip_populate (EContact *card,
                   gchar **values)
{
	EContactAddress *contact_addr = getormakeEContactAddress (card, E_CONTACT_ADDRESS_HOME);
	contact_addr->code = g_strdup (values[0]);
	e_contact_set (card, E_CONTACT_ADDRESS_HOME, contact_addr);
	e_contact_address_free (contact_addr);
}