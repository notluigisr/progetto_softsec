fix_bad_direct_key_sigs (kbnode_t keyblock, u32 *keyid)
{
  gpg_error_t err;
  kbnode_t node;
  int count = 0;

  for (node = keyblock->next; node; node=node->next)
    {
      if (node->pkt->pkttype == PKT_USER_ID)
        break;
      if (node->pkt->pkttype == PKT_SIGNATURE
          && IS_KEY_SIG (node->pkt->pkt.signature))
        {
          err = check_key_signature (keyblock, node, NULL);
          if (err && gpg_err_code (err) != GPG_ERR_PUBKEY_ALGO )
            {
              
              log_info ("STR",
                        keystr (keyid));
              delete_kbnode (node);
              count++;
            }
        }
    }

  return count;
}