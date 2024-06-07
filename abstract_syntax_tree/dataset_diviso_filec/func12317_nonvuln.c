spa_build_auth_challenge (SPAAuthRequest * request, SPAAuthChallenge * challenge)
{
char chalstr[8];
int i;
int p = (int)getpid();
int random_seed = (int)time(NULL) ^ ((p << 16) | p);

request = request;  



memset(challenge, 0, sizeof(SPAAuthChallenge));

challenge->bufIndex = 0;
memcpy (challenge->ident, "STR", 8);
SIVAL (&challenge->msgType, 0, 2);
SIVAL (&challenge->flags, 0, 0x00008201);
SIVAL (&challenge->uDomain.len, 0, 0x0000);
SIVAL (&challenge->uDomain.maxlen, 0, 0x0000);
SIVAL (&challenge->uDomain.offset, 0, 0x00002800);



for(i=0;i<8;i++)
  {
  chalstr[i] = (uschar)(random_seed >> 16) % 256;
  random_seed = (1103515245 - (chalstr[i])) * random_seed + 12345;
  }

memcpy(challenge->challengeData,chalstr,8);
}