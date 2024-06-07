calc_enc_length (gnutls_session_t session, int data_size,
                 int hash_size, uint8_t * pad, int random_pad,
                 cipher_type_t block_algo, uint16_t blocksize)
{
  uint8_t rnd;
  int length, ret;

  *pad = 0;

  switch (block_algo)
    {
    case CIPHER_STREAM:
      length = data_size + hash_size;

      break;
    case CIPHER_BLOCK:
      ret = _gnutls_rnd (GNUTLS_RND_NONCE, &rnd, 1);
      if (ret < 0)
        {
          gnutls_assert ();
          return ret;
        }

      
      if (session->security_parameters.version == GNUTLS_SSL3 ||
          random_pad == 0)
        {
          rnd = 0;
        }
      else
        {
          rnd = (rnd / blocksize) * blocksize;
          
          if (rnd > blocksize)
            rnd -= blocksize;
        }

      length = data_size + hash_size;

      *pad = (uint8_t) (blocksize - (length % blocksize)) + rnd;

      length += *pad;
      if (_gnutls_version_has_explicit_iv
          (session->security_parameters.version))
        length += blocksize;    

      break;
    default:
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }

  return length;
}