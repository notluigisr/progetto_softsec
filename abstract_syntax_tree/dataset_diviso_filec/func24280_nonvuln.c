mail_part_constructed (GObject *object)
{
	
	G_OBJECT_CLASS (e_mail_part_parent_class)->constructed (object);

	e_extensible_load_extensions (E_EXTENSIBLE (object));
}