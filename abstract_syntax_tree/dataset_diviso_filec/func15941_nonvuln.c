bool Curl_conncache_return_conn(struct Curl_easy *data,
                                struct connectdata *conn)
{
  
  size_t maxconnects =
    (data->multi->maxconnects < 0) ? data->multi->num_easy * 4:
    data->multi->maxconnects;
  struct connectdata *conn_candidate = NULL;

  conn->lastused = Curl_now(); 
  if(maxconnects > 0 &&
     Curl_conncache_size(data) > maxconnects) {
    infof(data, "STR");

    conn_candidate = Curl_conncache_extract_oldest(data);
    if(conn_candidate) {
      
      Curl_disconnect(data, conn_candidate,  FALSE);
    }
  }

  return (conn_candidate == conn) ? FALSE : TRUE;

}