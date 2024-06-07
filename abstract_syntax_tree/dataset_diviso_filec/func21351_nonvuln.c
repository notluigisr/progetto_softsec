static bool pickoneauth(struct auth *pick, unsigned long mask)
{
  bool picked;
  
  unsigned long avail = pick->avail & pick->want & mask;
  picked = TRUE;

  
  if(avail & CURLAUTH_NEGOTIATE)
    pick->picked = CURLAUTH_NEGOTIATE;
  else if(avail & CURLAUTH_BEARER)
    pick->picked = CURLAUTH_BEARER;
  else if(avail & CURLAUTH_DIGEST)
    pick->picked = CURLAUTH_DIGEST;
  else if(avail & CURLAUTH_NTLM)
    pick->picked = CURLAUTH_NTLM;
  else if(avail & CURLAUTH_NTLM_WB)
    pick->picked = CURLAUTH_NTLM_WB;
  else if(avail & CURLAUTH_BASIC)
    pick->picked = CURLAUTH_BASIC;
  else if(avail & CURLAUTH_AWS_SIGV4)
    pick->picked = CURLAUTH_AWS_SIGV4;
  else {
    pick->picked = CURLAUTH_PICKNONE; 
    picked = FALSE;
  }
  pick->avail = CURLAUTH_NONE; 

  return picked;
}