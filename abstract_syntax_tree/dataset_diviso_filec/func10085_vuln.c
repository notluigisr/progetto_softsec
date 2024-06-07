gdk_pixbuf__png_image_stop_load (gpointer context, GError **error)
{
        LoadContext* lc = context;

        g_return_val_if_fail(lc != NULL, TRUE);

        
        
        gdk_pixbuf_unref(lc->pixbuf);
        
        png_destroy_read_struct(&lc->png_read_ptr, NULL, NULL);
        g_free(lc);

        return TRUE;
}