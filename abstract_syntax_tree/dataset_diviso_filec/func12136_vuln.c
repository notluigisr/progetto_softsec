gdk_pixbuf_loader_write (GdkPixbufLoader *loader,
			 const guchar    *buf,
			 gsize            count,
                         GError         **error)
{
  GdkPixbufLoaderPrivate *priv;
  
  g_return_val_if_fail (loader != NULL, FALSE);
  g_return_val_if_fail (GDK_IS_PIXBUF_LOADER (loader), FALSE);
  
  g_return_val_if_fail (buf != NULL, FALSE);
  g_return_val_if_fail (count >= 0, FALSE);
  
  priv = loader->priv;
  
  
  g_return_val_if_fail (priv->closed == FALSE, FALSE);
  
  if (priv->image_module == NULL)
    {
      gint eaten;
      
      eaten = gdk_pixbuf_loader_eat_header_write (loader, buf, count, error);
      if (eaten <= 0)
	return FALSE;
      
      count -= eaten;
      buf += eaten;
    }
  
  if (count > 0 && priv->image_module->load_increment)
    {
      gboolean retval;
      retval = priv->image_module->load_increment (priv->context, buf, count,
                                                   error);
      if (!retval && error && *error == NULL)
        {
          
          g_warning ("STR",
                     priv->image_module->module_name);
          g_set_error (error,
                       GDK_PIXBUF_ERROR,
                       GDK_PIXBUF_ERROR_FAILED,
                       _("STR"
                         "STR"
                         "STR"),
                       priv->image_module->module_name);
        }

      return retval;
    }
      
  return TRUE;
}