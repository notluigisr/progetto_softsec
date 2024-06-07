int sftp_mkdir(sftp_session sftp, const char *directory, mode_t mode) {
  sftp_status_message status = NULL;
  sftp_message msg = NULL;
  sftp_attributes errno_attr = NULL;
  struct sftp_attributes_struct attr;
  ssh_buffer buffer;
  ssh_string path;
  uint32_t id;

  buffer = ssh_buffer_new();
  if (buffer == NULL) {
    ssh_set_error_oom(sftp->session);
    return -1;
  }

  path = ssh_string_from_char(directory);
  if (path == NULL) {
    ssh_set_error_oom(sftp->session);
    ssh_buffer_free(buffer);
    return -1;
  }

  ZERO_STRUCT(attr);
  attr.permissions = mode;
  attr.flags = SSH_FILEXFER_ATTR_PERMISSIONS;

  id = sftp_get_new_id(sftp);
  if (buffer_add_u32(buffer, id) < 0 ||
      buffer_add_ssh_string(buffer, path) < 0 ||
      buffer_add_attributes(buffer, &attr) < 0 ||
      sftp_packet_write(sftp, SSH_FXP_MKDIR, buffer) < 0) {
    ssh_buffer_free(buffer);
    ssh_string_free(path);
  }
  ssh_buffer_free(buffer);
  ssh_string_free(path);

  while (msg == NULL) {
    if (sftp_read_and_dispatch(sftp) < 0) {
      return -1;
    }
    msg = sftp_dequeue(sftp, id);
  }

  
  if (msg->packet_type == SSH_FXP_STATUS) {
    status = parse_status_msg(msg);
    sftp_message_free(msg);
    if (status == NULL) {
      return -1;
    }
    sftp_set_error(sftp, status->status);
    switch (status->status) {
      case SSH_FX_FAILURE:
        
        errno_attr = sftp_lstat(sftp, directory);
        if (errno_attr != NULL) {
          SAFE_FREE(errno_attr);
          sftp_set_error(sftp, SSH_FX_FILE_ALREADY_EXISTS);
        }
        break;
      case SSH_FX_OK:
        status_msg_free(status);
        return 0;
        break;
      default:
        break;
    }
    
    ssh_set_error(sftp->session, SSH_REQUEST_DENIED,
        "STR", status->errormsg);
    status_msg_free(status);
    return -1;
  } else {
    ssh_set_error(sftp->session, SSH_FATAL,
        "STR",
        msg->packet_type);
    sftp_message_free(msg);
  }

  return -1;
}