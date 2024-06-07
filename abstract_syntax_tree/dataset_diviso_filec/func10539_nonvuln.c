rfbBool rfbCheckPasswordByList(rfbClientPtr cl,const char* response,int len)
{
  char **passwds;
  int i=0;

  for(passwds=(char**)cl->screen->authPasswdData;*passwds;passwds++,i++) {
    uint8_t auth_tmp[CHALLENGESIZE];
    memcpy((char *)auth_tmp, (char *)cl->authChallenge, CHALLENGESIZE);
    rfbEncryptBytes(auth_tmp, *passwds);

    if (memcmp(auth_tmp, response, len) == 0) {
      if(i>=cl->screen->authPasswdFirstViewOnly)
	cl->viewOnly=TRUE;
      return(TRUE);
    }
  }

  rfbErr("STR",
	 cl->host);
  return(FALSE);
}