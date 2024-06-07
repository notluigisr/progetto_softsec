static void setup_des_key(const unsigned char *key_56,
                          DES_key_schedule DESKEYARG(ks))
{
  DES_cblock key;

  
  extend_key_56_to_64(key_56, (char *) &key);

  
  DES_set_odd_parity(&key);

  
  DES_set_key(&key, ks);
}