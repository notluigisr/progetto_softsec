static int ossl_get_ssl_sockindex_index(void)
{
  static int ssl_ex_data_sockindex_index = -1;
  if(ssl_ex_data_sockindex_index < 0) {
    ssl_ex_data_sockindex_index = SSL_get_ex_new_index(0, NULL, NULL, NULL,
        NULL);
  }
  return ssl_ex_data_sockindex_index;
}