static bool allow_auth_to_host(struct Curl_easy *data)
{
  struct connectdata *conn = data->conn;
  return (!data->state.this_is_a_follow ||
          data->set.allow_auth_to_other_hosts ||
          (data->state.first_host &&
           strcasecompare(data->state.first_host, conn->host.name) &&
           (data->state.first_remote_port == conn->remote_port) &&
           (data->state.first_remote_protocol == conn->handler->protocol)));
}