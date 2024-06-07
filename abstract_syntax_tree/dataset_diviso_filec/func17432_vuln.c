gdk_pixbuf_loader_close (GdkPixbufLoader *loader,
                         GError         **error)
{
  GdkPixbufLoaderPrivate *priv;
  gboolean retval = TRUE;
  
  g_return_val_if_fail (loader != NULL, TRUE);
  g_return_val_if_fail (GDK_IS_PIXBUF_LOADER (loader), TRUE);
  
  priv = loader->priv;
  
  
  g_return_val_if_fail (priv->closed == FALSE, TRUE);
  
  
  if (priv->image_module == NULL)
    gdk_pixbuf_loader_load_module (loader, NULL, NULL);
  
  if (priv->image_module && priv->image_module->stop_load)
    retval = priv->image_module->stop_load (priv->context, error);
  
  priv->closed = TRUE;
  
  g_signal_emit (G_OBJECT (loader), pixbuf_loader_signals[CLOSED], 0);

  return retval;
}