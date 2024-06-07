httpFreeCredentials(
    cups_array_t *credentials)		
{
  http_credential_t	*credential;	


  for (credential = (http_credential_t *)cupsArrayFirst(credentials);
       credential;
       credential = (http_credential_t *)cupsArrayNext(credentials))
  {
    cupsArrayRemove(credentials, credential);
    free((void *)credential->data);
    free(credential);
  }

  cupsArrayDelete(credentials);
}