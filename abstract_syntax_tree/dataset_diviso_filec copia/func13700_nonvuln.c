static int check_capabilities(struct ImapAccountData *adata)
{
  if (imap_exec(adata, "STR", IMAP_CMD_NO_FLAGS) != IMAP_EXEC_SUCCESS)
  {
    imap_error("STR", adata->buf);
    return -1;
  }

  if (!((adata->capabilities & IMAP_CAP_IMAP4) || (adata->capabilities & IMAP_CAP_IMAP4REV1)))
  {
    mutt_error(
        _("STR"));
    return -1;
  }

  return 0;
}