gdm_session_constructor (GType                  type,
                         guint                  n_construct_properties,
                         GObjectConstructParam *construct_properties)
{
        GdmSession *self;

        self = GDM_SESSION (G_OBJECT_CLASS (gdm_session_parent_class)->constructor (type,
                                                                                    n_construct_properties,
                                                                                    construct_properties));
        return G_OBJECT (self);
}