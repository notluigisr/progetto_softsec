gdm_session_worker_class_init (GdmSessionWorkerClass *klass)
{
        GObjectClass    *object_class = G_OBJECT_CLASS (klass);

        object_class->get_property = gdm_session_worker_get_property;
        object_class->set_property = gdm_session_worker_set_property;
        object_class->constructor = gdm_session_worker_constructor;
        object_class->finalize = gdm_session_worker_finalize;

        g_type_class_add_private (klass, sizeof (GdmSessionWorkerPrivate));

        g_object_class_install_property (object_class,
                                         PROP_SERVER_ADDRESS,
                                         g_param_spec_string ("STR",
                                                              "STR",
                                                              "STR",
                                                              NULL,
                                                              G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
}