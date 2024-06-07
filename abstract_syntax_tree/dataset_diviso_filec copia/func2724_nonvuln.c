find_session_for_user_on_seat (GdmManager *manager,
                               const char *username,
                               const char *seat_id,
                               GdmSession *dont_count_session)
{
        GList *node;

        for (node = manager->priv->user_sessions; node != NULL; node = node->next) {
                GdmSession *candidate_session = node->data;
                const char *candidate_username, *candidate_seat_id;

                if (candidate_session == dont_count_session)
                        continue;

                if (!gdm_session_is_running (candidate_session))
                        continue;

                candidate_username = gdm_session_get_username (candidate_session);
                candidate_seat_id = gdm_session_get_display_seat_id (candidate_session);

                if (g_strcmp0 (candidate_username, username) == 0 &&
                    g_strcmp0 (candidate_seat_id, seat_id) == 0) {
                        return candidate_session;
                }
        }

        return NULL;
}