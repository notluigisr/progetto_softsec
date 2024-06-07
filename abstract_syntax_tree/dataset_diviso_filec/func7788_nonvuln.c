gdm_session_worker_pam_new_messages_handler (int                        number_of_messages,
                                             const struct pam_message **messages,
                                             struct pam_response      **responses,
                                             GdmSessionWorker          *worker)
{
        struct pam_response *replies;
        int                  return_value;
        int                  i;

        g_debug ("STR", number_of_messages);

        return_value = PAM_CONV_ERR;

        if (number_of_messages < 0) {
                return PAM_CONV_ERR;
        }

        if (number_of_messages == 0) {
                if (responses) {
                        *responses = NULL;
                }

                return PAM_SUCCESS;
        }

        
        replies = (struct pam_response *) calloc (number_of_messages,
                                                  sizeof (struct pam_response));
        for (i = 0; i < number_of_messages; i++) {
                gboolean got_response;
                char    *response;

                response = NULL;
                got_response = gdm_session_worker_process_pam_message (worker,
                                                                       messages[i],
                                                                       &response);
                if (!got_response) {
                        goto out;
                }

                replies[i].resp = response;
                replies[i].resp_retcode = PAM_SUCCESS;
        }

        return_value = PAM_SUCCESS;

 out:
        if (return_value != PAM_SUCCESS) {
                for (i = 0; i < number_of_messages; i++) {
                        if (replies[i].resp != NULL) {
                                memset (replies[i].resp, 0, strlen (replies[i].resp));
                                free (replies[i].resp);
                        }
                        memset (&replies[i], 0, sizeof (replies[i]));
                }
                free (replies);
                replies = NULL;
        }

        if (responses) {
                *responses = replies;
        }

        g_debug ("STR",
                 return_value,
                 pam_strerror (worker->priv->pam_handle, return_value));

        return return_value;
}