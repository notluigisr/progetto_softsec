static size_t ossl_version(char *buffer, size_t size)
{
#ifdef LIBRESSL_VERSION_NUMBER
#if LIBRESSL_VERSION_NUMBER < 0x2070100fL
  return msnprintf(buffer, size, "STR",
                   OSSL_PACKAGE,
                   (LIBRESSL_VERSION_NUMBER>>28)&0xf,
                   (LIBRESSL_VERSION_NUMBER>>20)&0xff,
                   (LIBRESSL_VERSION_NUMBER>>12)&0xff);
#else 
  char *p;
  int count;
  const char *ver = OpenSSL_version(OPENSSL_VERSION);
  const char expected[] = OSSL_PACKAGE "STR" */
  if(Curl_strncasecompare(ver, expected, sizeof(expected) - 1)) {
    ver += sizeof(expected) - 1;
  }
  count = msnprintf(buffer, size, "STR", OSSL_PACKAGE, ver);
  for(p = buffer; *p; ++p) {
    if(ISSPACE(*p))
      *p = '_';
  }
  return count;
#endif
#elif defined(OPENSSL_IS_BORINGSSL)
  return msnprintf(buffer, size, OSSL_PACKAGE);
#elif defined(HAVE_OPENSSL_VERSION) && defined(OPENSSL_VERSION_STRING)
  return msnprintf(buffer, size, "STR",
                   OSSL_PACKAGE, OpenSSL_version(OPENSSL_VERSION_STRING));
#else
  

  char sub[3];
  unsigned long ssleay_value;
  sub[2]='\0';
  sub[1]='\0';
  ssleay_value = OpenSSL_version_num();
  if(ssleay_value < 0x906000) {
    ssleay_value = SSLEAY_VERSION_NUMBER;
    sub[0]='\0';
  }
  else {
    if(ssleay_value&0xff0) {
      int minor_ver = (ssleay_value >> 4) & 0xff;
      if(minor_ver > 26) {
        
        sub[1] = (char) ((minor_ver - 1) % 26 + 'a' + 1);
        sub[0] = 'z';
      }
      else {
        sub[0] = (char) (minor_ver + 'a' - 1);
      }
    }
    else
      sub[0]='\0';
  }

  return msnprintf(buffer, size, "STR"
#ifdef OPENSSL_FIPS
                   "STR"
#endif
                   ,
                   OSSL_PACKAGE,
                   (ssleay_value>>28)&0xf,
                   (ssleay_value>>20)&0xff,
                   (ssleay_value>>12)&0xff,
                   sub);
#endif 
}