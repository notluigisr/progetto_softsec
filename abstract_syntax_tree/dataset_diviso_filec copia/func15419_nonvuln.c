is_algo_in_prefs (kbnode_t keyblock, preftype_t type, int algo)
{
  kbnode_t k;

  for (k = keyblock; k; k = k->next)
    {
      if (k->pkt->pkttype == PKT_USER_ID)
        {
          PKT_user_id *uid = k->pkt->pkt.user_id;
          prefitem_t *prefs = uid->prefs;

          if (uid->created && prefs && !uid->is_revoked && !uid->is_expired)
            {
              for (; prefs->type; prefs++)
                if (prefs->type == type && prefs->value == algo)
                  return 1;
            }
        }
    }
  return 0;
}