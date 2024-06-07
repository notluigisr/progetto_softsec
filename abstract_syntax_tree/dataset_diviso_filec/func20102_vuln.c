int ssh_scp_write(ssh_scp scp, const void *buffer, size_t len){
  int w;
  int r;
  uint8_t code;
  if(scp==NULL)
      return SSH_ERROR;
  if(scp->state != SSH_SCP_WRITE_WRITING){
    ssh_set_error(scp->session,SSH_FATAL,"STR");
    return SSH_ERROR;
  }
  if(scp->processed + len > scp->filelen)
    len = (size_t) (scp->filelen - scp->processed);
  
  r = ssh_channel_poll(scp->channel, 0);
  if (r == SSH_ERROR) {
      scp->state = SSH_SCP_ERROR;
      return SSH_ERROR;
  }
  w=ssh_channel_write(scp->channel,buffer,len);
  if(w != SSH_ERROR)
    scp->processed += w;
  else {
    scp->state=SSH_SCP_ERROR;
    
    return SSH_ERROR;
  }
  
  r = ssh_channel_poll(scp->channel,0);
  if(r > 0){
    r = ssh_channel_read(scp->channel, &code, 1, 0);
    if(r == SSH_ERROR){
      return SSH_ERROR;
    }
    if(code == 1 || code == 2){
      ssh_set_error(scp->session,SSH_REQUEST_DENIED, "STR", code);
      return SSH_ERROR;
    }
  }
  
  if(scp->processed == scp->filelen) {
    code = 0;
    w = ssh_channel_write(scp->channel, &code, 1);
    if(w == SSH_ERROR){
      scp->state = SSH_SCP_ERROR;
      return SSH_ERROR;
    }
    scp->processed=scp->filelen=0;
    scp->state=SSH_SCP_WRITE_INITED;
  }
  return SSH_OK;
}