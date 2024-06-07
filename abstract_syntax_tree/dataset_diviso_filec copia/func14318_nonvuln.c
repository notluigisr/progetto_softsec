static int nntp_connect_error(struct NntpServer *nserv)
{
  nserv->status = NNTP_NONE;
  mutt_error(_("STR"));
  return -1;
}