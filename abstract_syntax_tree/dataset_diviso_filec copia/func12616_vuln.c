static void dummy_wait(record_parameters_st * params, gnutls_datum_t* plaintext, 
                       unsigned pad_failed, unsigned int pad, unsigned total)
{
  
  if (_gnutls_cipher_is_block (params->cipher_algorithm) == CIPHER_BLOCK)
    {
      unsigned len;

      
      if (pad_failed == 0 && pad > 0) 
        {
          len = _gnutls_get_hash_block_len(params->mac_algorithm);
          if (len > 0)
            {
              
	      if ((pad+total) % len > len-9 && total % len <= len-9) 
	        {
	          if (len < plaintext->size)
                    _gnutls_auth_cipher_add_auth (&params->read.cipher_state, plaintext->data, len);
                  else
                    _gnutls_auth_cipher_add_auth (&params->read.cipher_state, plaintext->data, plaintext->size);
                }
            }
        }
    }
}