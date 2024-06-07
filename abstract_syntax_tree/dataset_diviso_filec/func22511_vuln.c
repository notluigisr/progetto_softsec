int main(int argc,char** argv)
{
  char *repeaterHost;
  int repeaterPort, sock;
  char id[250];
  rfbClientPtr cl;

  int i,j;
  uint16_t* f;

  
  if (argc < 3) {
    fprintf(stderr,
      "STR", argv[0]);
    exit(1);
  }
  snprintf(id, sizeof(id) - 1, "STR", argv[1]);
  repeaterHost = argv[2];
  repeaterPort = argc < 4 ? 5500 : atoi(argv[3]);

  
  rfbScreenInfoPtr server=rfbGetScreen(&argc,argv,400,300,5,3,2);
  if(!server)
    return 0;
  server->frameBuffer=(char*)malloc(400*300*2);
  f=(uint16_t*)server->frameBuffer;
  for(j=0;j<300;j++)
    for(i=0;i<400;i++)
      f[j*400+i]= ((j*32/300) << 10) |
		  (((j+400-i)*32/700) << 5) |
		  ((i*32/400));

  
  server->port = -1; 
  server->ipv6port = -1; 

  sock = rfbConnectToTcpAddr(repeaterHost, repeaterPort);
  if (sock < 0) {
    perror("STR");
    return 1;
  }
  if (write(sock, id, sizeof(id)) != sizeof(id)) {
    perror("STR");
    return 1;
  }
  cl = rfbNewClient(server, sock);
  if (!cl) {
    perror("STR");
    return 1;
  }
  cl->reverseConnection = 0;
  cl->clientGoneHook = clientGone;

  
  rfbInitServer(server);
  rfbRunEventLoop(server,-1,FALSE);

  return 0;
}