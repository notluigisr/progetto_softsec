static bool schannel_data_pending(const struct connectdata *conn,
                                  int sockindex)
{
  const struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(connssl->use) 
    return (BACKEND->decdata_offset > 0 ||
            (BACKEND->encdata_offset > 0 && !BACKEND->encdata_is_incomplete));
  else
    return FALSE;
}