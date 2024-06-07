ms_response_get_basename (MsResponse *response)
{
  return http_path_get_basename (response->path);
}