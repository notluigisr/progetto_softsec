gs_listener_new (void)
{
        GSListener *listener;

        listener = g_object_new (GS_TYPE_LISTENER, NULL);

        return GS_LISTENER (listener);
}