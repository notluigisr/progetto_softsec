static void imap_to_imaps(struct connectdata *conn)
{
  
  conn->handler = &Curl_handler_imaps;

  
  conn->tls_upgraded = TRUE;
}