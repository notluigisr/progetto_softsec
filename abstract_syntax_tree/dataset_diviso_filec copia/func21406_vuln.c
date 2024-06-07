static int channel_setenv(LIBSSH2_CHANNEL *channel,
                          const char *varname, unsigned int varname_len,
                          const char *value, unsigned int value_len)
{
    LIBSSH2_SESSION *session = channel->session;
    unsigned char *s, *data;
    static const unsigned char reply_codes[3] =
        { SSH_MSG_CHANNEL_SUCCESS, SSH_MSG_CHANNEL_FAILURE, 0 };
    size_t data_len;
    int rc;

    if(channel->setenv_state == libssh2_NB_state_idle) {
        
        channel->setenv_packet_len = varname_len + value_len + 21;

        
        memset(&channel->setenv_packet_requirev_state, 0,
               sizeof(channel->setenv_packet_requirev_state));

        _libssh2_debug(session, LIBSSH2_TRACE_CONN,
                       "STR"
                       "STR",
                       varname, value, channel->local.id, channel->remote.id);

        s = channel->setenv_packet =
            LIBSSH2_ALLOC(session, channel->setenv_packet_len);
        if(!channel->setenv_packet) {
            return _libssh2_error(session, LIBSSH2_ERROR_ALLOC,
                                  "STR"
                                  "STR");
        }

        *(s++) = SSH_MSG_CHANNEL_REQUEST;
        _libssh2_store_u32(&s, channel->remote.id);
        _libssh2_store_str(&s, "STR") - 1);
        *(s++) = 0x01;
        _libssh2_store_str(&s, varname, varname_len);
        _libssh2_store_str(&s, value, value_len);

        channel->setenv_state = libssh2_NB_state_created;
    }

    if(channel->setenv_state == libssh2_NB_state_created) {
        rc = _libssh2_transport_send(session,
                                     channel->setenv_packet,
                                     channel->setenv_packet_len,
                                     NULL, 0);
        if(rc == LIBSSH2_ERROR_EAGAIN) {
            _libssh2_error(session, rc,
                           "STR");
            return rc;
        }
        else if(rc) {
            LIBSSH2_FREE(session, channel->setenv_packet);
            channel->setenv_packet = NULL;
            channel->setenv_state = libssh2_NB_state_idle;
            return _libssh2_error(session, LIBSSH2_ERROR_SOCKET_SEND,
                                  "STR"
                                  "STR");
        }
        LIBSSH2_FREE(session, channel->setenv_packet);
        channel->setenv_packet = NULL;

        _libssh2_htonu32(channel->setenv_local_channel, channel->local.id);

        channel->setenv_state = libssh2_NB_state_sent;
    }

    if(channel->setenv_state == libssh2_NB_state_sent) {
        rc = _libssh2_packet_requirev(session, reply_codes, &data, &data_len,
                                      1, channel->setenv_local_channel, 4,
                                      &channel->
                                      setenv_packet_requirev_state);
        if(rc == LIBSSH2_ERROR_EAGAIN) {
            return rc;
        }
        if(rc) {
            channel->setenv_state = libssh2_NB_state_idle;
            return rc;
        }

        if(data[0] == SSH_MSG_CHANNEL_SUCCESS) {
            LIBSSH2_FREE(session, data);
            channel->setenv_state = libssh2_NB_state_idle;
            return 0;
        }

        LIBSSH2_FREE(session, data);
    }

    channel->setenv_state = libssh2_NB_state_idle;
    return _libssh2_error(session, LIBSSH2_ERROR_CHANNEL_REQUEST_DENIED,
                          "STR");
}