rsvg_handle_close (RsvgHandle * handle, GError ** error)
{
    RsvgHandlePrivate *priv;

    rsvg_return_val_if_fail (handle, FALSE, error);
    priv = handle->priv;

    if (priv->is_closed)
          return TRUE;

#if GLIB_CHECK_VERSION (2, 24, 0)
    if (priv->data_input_stream) {
        GConverter *converter;
        GInputStream *stream;
        gboolean ret;

        converter = G_CONVERTER (g_zlib_decompressor_new (G_ZLIB_COMPRESSOR_FORMAT_GZIP));
        stream = g_converter_input_stream_new (priv->data_input_stream, converter);
        g_object_unref (converter);
        g_object_unref (priv->data_input_stream);
        priv->data_input_stream = NULL;

        ret = rsvg_handle_read_stream_sync (handle, stream, NULL, error);
        g_object_unref (stream);

        return ret;
    }
#elif defined(HAVE_GSF)
    if (priv->gzipped_data) {
        GsfInput *gzip;
        const guchar *bytes;
        gsize size;
        gsize remaining;

        bytes = gsf_output_memory_get_bytes (GSF_OUTPUT_MEMORY (priv->gzipped_data));
        size = gsf_output_size (priv->gzipped_data);

        gzip =
            GSF_INPUT (gsf_input_gzip_new
                       (GSF_INPUT (gsf_input_memory_new (bytes, size, FALSE)), error));
        remaining = gsf_input_remaining (gzip);
        while ((size = MIN (remaining, 1024)) > 0) {
            guint8 const *buf;

            
            buf = gsf_input_read (gzip, size, NULL);
            if (!buf) {
                
                g_warning (_("STR"));
                break;
            }

            rsvg_handle_write_impl (handle, buf, size, error);
            
            if (remaining == ((gsize) gsf_input_remaining (gzip))) {
                g_warning (_
                           ("STR"));
                break;
            }
            remaining = gsf_input_remaining (gzip);
        }
        g_object_unref (gzip);

        
        gsf_output_close (priv->gzipped_data);
        g_object_unref (priv->gzipped_data);
        priv->gzipped_data = NULL;
    }
#endif 

    return rsvg_handle_close_impl (handle, error);
}