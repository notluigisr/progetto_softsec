gdm_session_reset (GdmSession *self)
{
        if (self->priv->user_verifier_interface != NULL) {
                gdm_dbus_user_verifier_emit_reset (self->priv->user_verifier_interface);
        }

        do_reset (self);
}