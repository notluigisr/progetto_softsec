HttpTransact::bootstrap_state_variables_from_request(State* s, HTTPHdr* incoming_request)
{
  s->current.now = s->client_request_time = ink_cluster_time();
  s->client_info.http_version = incoming_request->version_get();
}