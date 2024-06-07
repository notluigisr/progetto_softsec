Curl_ssl_config_matches(struct ssl_primary_config *data,
                        struct ssl_primary_config *needle)
{
  if((data->version == needle->version) &&
     (data->version_max == needle->version_max) &&
     (data->verifypeer == needle->verifypeer) &&
     (data->verifyhost == needle->verifyhost) &&
     (data->verifystatus == needle->verifystatus) &&
     blobcmp(data->cert_blob, needle->cert_blob) &&
     blobcmp(data->ca_info_blob, needle->ca_info_blob) &&
     blobcmp(data->issuercert_blob, needle->issuercert_blob) &&
     safecmp(data->CApath, needle->CApath) &&
     safecmp(data->CAfile, needle->CAfile) &&
     safecmp(data->issuercert, needle->issuercert) &&
     safecmp(data->clientcert, needle->clientcert) &&
     safecmp(data->random_file, needle->random_file) &&
     safecmp(data->egdsocket, needle->egdsocket) &&
     Curl_safe_strcasecompare(data->cipher_list, needle->cipher_list) &&
     Curl_safe_strcasecompare(data->cipher_list13, needle->cipher_list13) &&
     Curl_safe_strcasecompare(data->curves, needle->curves) &&
     Curl_safe_strcasecompare(data->pinned_key, needle->pinned_key))
    return TRUE;

  return FALSE;
}