file_proxy(const char *url)	
{
   char	scheme[HTTP_MAX_URI],	
	username[HTTP_MAX_URI],	
	hostname[HTTP_MAX_URI],	
	resource[HTTP_MAX_URI];	
  int	port;			


  if (url == NULL || url[0] == '\0')
  {
    proxy_host[0] = '\0';
    proxy_port    = 0;
  }
  else
  {
    httpSeparateURI(HTTP_URI_CODING_ALL, url, scheme, sizeof(scheme),
                    username, sizeof(username), hostname, sizeof(hostname),
		    &port, resource, sizeof(resource));

    if (strcmp(scheme, "STR") == 0)
    {
      strlcpy(proxy_host, hostname, sizeof(proxy_host));
      proxy_port = port;
    }
  }
}