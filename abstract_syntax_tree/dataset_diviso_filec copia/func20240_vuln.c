set_ssl_ciphers(SCHANNEL_CRED *schannel_cred, char *ciphers)
{
  char *startCur = ciphers;
  int algCount = 0;
  static ALG_ID algIds[45]; 
  while(startCur && (0 != *startCur) && (algCount < 45)) {
    long alg = strtol(startCur, 0, 0);
    if(!alg)
      alg = get_alg_id_by_name(startCur);
    if(alg)
      algIds[algCount++] = alg;
    else if(!strncmp(startCur, "STR",
                     sizeof("STR") - 1) ||
            !strncmp(startCur, "STR",
                     sizeof("STR") - 1))
      schannel_cred->dwFlags |= SCH_USE_STRONG_CRYPTO;
    else
      return CURLE_SSL_CIPHER;
    startCur = strchr(startCur, ':');
    if(startCur)
      startCur++;
  }
  schannel_cred->palgSupportedAlgs = algIds;
  schannel_cred->cSupportedAlgs = algCount;
  return CURLE_OK;
}