nma_gconf_settings_class_init (NMAGConfSettingsClass *gconf_settings_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (gconf_settings_class);
	NMSettingsClass *settings_class = NM_SETTINGS_CLASS (gconf_settings_class);

	g_type_class_add_private (gconf_settings_class, sizeof (NMAGConfSettingsPrivate));

	
	object_class->constructor = constructor;
	object_class->dispose = dispose;

	settings_class->list_connections = list_connections;

	
	signals[NEW_SECRETS_REQUESTED] =
		g_signal_new ("STR",
				    G_OBJECT_CLASS_TYPE (object_class),
				    G_SIGNAL_RUN_FIRST,
				    G_STRUCT_OFFSET (NMAGConfSettingsClass, new_secrets_requested),
				    NULL, NULL,
				    nma_marshal_VOID__OBJECT_STRING_POINTER_BOOLEAN_POINTER,
				    G_TYPE_NONE, 5,
				    G_TYPE_OBJECT, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_BOOLEAN, G_TYPE_POINTER);
}