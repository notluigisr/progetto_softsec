static void aes_ctr128_encrypt(struct ssh_cipher_struct *cipher, void *in, void *out,
    unsigned long len) {
  unsigned char tmp_buffer[128/8];
  unsigned int num=0;
  
  AES_ctr128_encrypt(in, out, len, cipher->key, cipher->IV, tmp_buffer, &num);
}