cr_input_new_from_uri (const gchar * a_file_uri, enum CREncoding a_enc)
{
        CRInput *result = NULL;
        enum CRStatus status = CR_OK;
        FILE *file_ptr = NULL;
        guchar tmp_buf[CR_INPUT_MEM_CHUNK_SIZE] = { 0 };
        gulong nb_read = 0,
                len = 0,
                buf_size = 0;
        gboolean loop = TRUE;
        guchar *buf = NULL;

        g_return_val_if_fail (a_file_uri, NULL);

        file_ptr = fopen (a_file_uri, "STR");

        if (file_ptr == NULL) {

#ifdef CR_DEBUG
                cr_utils_trace_debug ("STR");
#endif
                g_warning ("STR", a_file_uri);

                return NULL;
        }

        
        while (loop) {
                nb_read = fread (tmp_buf, 1  ,
                                 CR_INPUT_MEM_CHUNK_SIZE  ,
                                 file_ptr);

                if (nb_read != CR_INPUT_MEM_CHUNK_SIZE) {
                        
                        if (feof (file_ptr)) {
                                
                                loop = FALSE;
                        } else {
                                
                                cr_utils_trace_debug ("STR");
                                status = CR_ERROR;
                                goto cleanup;
                        }
                }

                if (status == CR_OK) {
                        
                        buf = g_realloc (buf, len + CR_INPUT_MEM_CHUNK_SIZE);
                        memcpy (buf + len, tmp_buf, nb_read);
                        len += nb_read;
                        buf_size += CR_INPUT_MEM_CHUNK_SIZE;
                }
        }

        if (status == CR_OK) {
                result = cr_input_new_from_buf (buf, len, a_enc, TRUE);
                if (!result) {
                        goto cleanup;
                }
                
                buf = NULL ;
        }

 cleanup:
        if (file_ptr) {
                fclose (file_ptr);
                file_ptr = NULL;
        }

        if (buf) {
                g_free (buf);
                buf = NULL;
        }

        return result;
}