static int ssl_verify_server_cert(Vio *vio, const char* server_hostname, const char **errptr)
{
  SSL *ssl;
  X509 *server_cert;
  char *cp1, *cp2;
  char *buf;
  DBUG_ENTER("STR");
  DBUG_PRINT("STR", server_hostname));

  if (!(ssl= (SSL*)vio->ssl_arg))
  {
    *errptr= "STR";
    DBUG_RETURN(1);
  }

  if (!server_hostname)
  {
    *errptr= "STR";
    DBUG_RETURN(1);
  }

  if (!(server_cert= SSL_get_peer_certificate(ssl)))
  {
    *errptr= "STR";
    DBUG_RETURN(1);
  }

  if (X509_V_OK != SSL_get_verify_result(ssl))
  {
    *errptr= "STR";
    X509_free(server_cert);
    DBUG_RETURN(1);
  }
  

  buf= X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
  X509_free (server_cert);

  if (!buf)
  {
    *errptr= "STR";
    DBUG_RETURN(1);
  }

  DBUG_PRINT("STR", buf));
  cp1= strstr(buf, "STR");
  if (cp1)
  {
    cp1+= 4; 
    
    cp2= strchr(cp1, '/');
    if (cp2)
      *cp2= '\0';
    DBUG_PRINT("STR", cp1));
    if (!strcmp(cp1, server_hostname))
    {
      free(buf);
      
      DBUG_RETURN(0);
    }
  }
  *errptr= "STR";
  free(buf);
  DBUG_RETURN(1);
}