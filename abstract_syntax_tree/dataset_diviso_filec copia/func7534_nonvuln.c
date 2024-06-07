static bool disconnect_if_dead(struct connectdata *conn,
                               struct Curl_easy *data)
{
  size_t pipeLen = conn->send_pipe.size + conn->recv_pipe.size;
  if(!pipeLen && !conn->inuse) {
    
    bool dead;

    if(conn->handler->connection_check) {
      
      unsigned int state;

      state = conn->handler->connection_check(conn, CONNCHECK_ISDEAD);
      dead = (state & CONNRESULT_DEAD);
    }
    else {
      
      dead = SocketIsDead(conn->sock[FIRSTSOCKET]);
    }

    if(dead) {
      conn->data = data;
      infof(data, "STR", conn->connection_id);

      
      Curl_disconnect(conn, TRUE);
      return TRUE;
    }
  }
  return FALSE;
}