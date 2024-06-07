anniversary_compare (EContact *contact1,
                     EContact *contact2)
{
	EContactDate *dt1, *dt2;
	gboolean equal;

	dt1 = e_contact_get (contact1, E_CONTACT_ANNIVERSARY);
	dt2 = e_contact_get (contact2, E_CONTACT_ANNIVERSARY);

	equal = e_contact_date_equal (dt1, dt2);

	e_contact_date_free (dt1);
	e_contact_date_free (dt2);

	return equal;
}