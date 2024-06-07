void Curl_attach_connnection(struct Curl_easy *data,
                             struct connectdata *conn)
{
  DEBUGASSERT(!data->conn);
  DEBUGASSERT(conn);
  data->conn = conn;
  Curl_llist_insert_next(&conn->easyq, conn->easyq.tail, data,
                         &data->conn_queue);
  if(conn->handler->attach)
    conn->handler->attach(data, conn);
}