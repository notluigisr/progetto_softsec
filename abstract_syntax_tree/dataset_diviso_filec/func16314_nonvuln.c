static int ossl_check_cxn(struct connectdata *conn)
{
  
#ifdef MSG_PEEK
  char buf;
  ssize_t nread;
  nread = recv((RECV_TYPE_ARG1)conn->sock[FIRSTSOCKET], (RECV_TYPE_ARG2)&buf,
               (RECV_TYPE_ARG3)1, (RECV_TYPE_ARG4)MSG_PEEK);
  if(nread == 0)
    return 0; 
  if(nread == 1)
    return 1; 
  else if(nread == -1) {
      int err = SOCKERRNO;
      if(err == EINPROGRESS ||
#if defined(EAGAIN) && (EAGAIN != EWOULDBLOCK)
         err == EAGAIN ||
#endif
         err == EWOULDBLOCK)
        return 1; 
      if(err == ECONNRESET ||
#ifdef ECONNABORTED
         err == ECONNABORTED ||
#endif
#ifdef ENETDOWN
         err == ENETDOWN ||
#endif
#ifdef ENETRESET
         err == ENETRESET ||
#endif
#ifdef ESHUTDOWN
         err == ESHUTDOWN ||
#endif
#ifdef ETIMEDOUT
         err == ETIMEDOUT ||
#endif
         err == ENOTCONN)
        return 0; 
  }
#endif
  return -1; 
}