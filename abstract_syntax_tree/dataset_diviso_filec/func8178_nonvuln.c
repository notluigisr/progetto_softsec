static CURLcode choose_mech(struct Curl_easy *data, struct connectdata *conn)
{
  int ret;
  void *tmp_allocation;
  const struct Curl_sec_client_mech *mech = &Curl_krb5_client_mech;

  tmp_allocation = realloc(conn->app_data, mech->size);
  if(!tmp_allocation) {
    failf(data, "STR", mech->size);
    mech = NULL;
    return CURLE_OUT_OF_MEMORY;
  }
  conn->app_data = tmp_allocation;

  if(mech->init) {
    ret = mech->init(conn->app_data);
    if(ret) {
      infof(data, "STR",
            mech->name);
      return CURLE_FAILED_INIT;
    }
  }

  infof(data, "STR", mech->name);
  ret = ftp_send_command(data, "STR", mech->name);
  if(ret < 0)
    return CURLE_COULDNT_CONNECT;

  if(ret/100 != 3) {
    switch(ret) {
    case 504:
      infof(data, "STR"
            "STR", mech->name);
      break;
    case 534:
      infof(data, "STR"
            "STR", mech->name);
      break;
    default:
      if(ret/100 == 5) {
        infof(data, "STR");
        return CURLE_USE_SSL_FAILED;
      }
      break;
    }
    return CURLE_LOGIN_DENIED;
  }

  
  ret = mech->auth(conn->app_data, data, conn);

  if(ret != AUTH_CONTINUE) {
    if(ret != AUTH_OK) {
      
      return CURLE_USE_SSL_FAILED;
    }
    DEBUGASSERT(ret == AUTH_OK);

    conn->mech = mech;
    conn->sec_complete = 1;
    conn->recv[FIRSTSOCKET] = sec_recv;
    conn->send[FIRSTSOCKET] = sec_send;
    conn->recv[SECONDARYSOCKET] = sec_recv;
    conn->send[SECONDARYSOCKET] = sec_send;
    conn->command_prot = PROT_SAFE;
    
    
    (void)sec_set_protection_level(data);
  }

  return CURLE_OK;
}