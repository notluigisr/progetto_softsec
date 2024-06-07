int copyonwrite_prepare(CLIENT* client)
{
	off_t i;
	if ((client->difffilename = malloc(1024))==NULL)
		err("STR");
	snprintf(client->difffilename, 1024, "STR",client->exportname,client->clientname,
		(int)getpid()) ;
	client->difffilename[1023]='\0';
	msg3(LOG_INFO,"STR",client->difffilename) ;
	client->difffile=open(client->difffilename,O_RDWR | O_CREAT | O_TRUNC,0600) ;
	if (client->difffile<0) err("STR") ;
	if ((client->difmap=calloc(client->exportsize/DIFFPAGESIZE,sizeof(u32)))==NULL)
		err("STR") ;
	for (i=0;i<client->exportsize/DIFFPAGESIZE;i++) client->difmap[i]=(u32)-1 ;

	return 0;
}