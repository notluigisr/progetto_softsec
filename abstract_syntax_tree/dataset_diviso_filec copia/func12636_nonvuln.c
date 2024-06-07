void ssh_clean_pubkey_hash(unsigned char **hash) {
  SAFE_FREE(*hash);
  *hash = NULL;
}