remove_lock_timer (GSManager *manager)
{
        if (manager->priv->lock_timeout_id != 0) {
                g_source_remove (manager->priv->lock_timeout_id);
                manager->priv->lock_timeout_id = 0;
        }
}