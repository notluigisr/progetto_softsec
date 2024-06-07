clean_key (kbnode_t keyblock, int noisy, int self_only,
           int *uids_cleaned, int *sigs_cleaned)
{
  kbnode_t uidnode;

  merge_keys_and_selfsig (keyblock);

  for (uidnode = keyblock->next;
       uidnode && uidnode->pkt->pkttype != PKT_PUBLIC_SUBKEY;
       uidnode = uidnode->next)
    {
      if (uidnode->pkt->pkttype == PKT_USER_ID)
        clean_one_uid (keyblock, uidnode,noisy, self_only,
                       uids_cleaned, sigs_cleaned);
    }
}