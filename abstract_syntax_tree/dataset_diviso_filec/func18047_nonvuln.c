static void SFDGetTtfInstrs(FILE *sfd, SplineChar *sc) {
    
    
    int i,len;
    struct enc85 dec;

    memset(&dec,'\0', sizeof(dec)); dec.pos = -1;
    dec.sfd = sfd;

    getint(sfd,&len);
    sc->ttf_instrs = malloc(len);
    sc->ttf_instrs_len = len;
    for ( i=0; i<len; ++i )
	sc->ttf_instrs[i] = Dec85(&dec);
}