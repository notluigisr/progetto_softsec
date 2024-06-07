Uz_Globs *globalsCtor()
{
#ifdef REENTRANT
    Uz_Globs *pG = (Uz_Globs *)malloc(sizeof(Uz_Globs));

    if (!pG)
        return (Uz_Globs *)NULL;
#endif 

    

    memzero(&G, sizeof(Uz_Globs));

#ifndef FUNZIP
#ifdef CMS_MVS
    uO.aflag=1;
    uO.C_flag=1;
#endif
#ifdef TANDEM
    uO.aflag=1;     
#endif
#ifdef VMS
# if (!defined(NO_TIMESTAMPS))
    uO.D_flag=1;    
# endif
#endif

    uO.lflag=(-1);
    G.wildzipfn = "";
    G.pfnames = (char **)fnames;
    G.pxnames = (char **)&fnames[1];
    G.pInfo = G.info;
    G.sol = TRUE;          

    G.message = UzpMessagePrnt;
    G.input = UzpInput;           
#if defined(WINDLL) || defined(MACOS)
    G.mpause = NULL;              
#else
    G.mpause = UzpMorePause;
#endif
    G.decr_passwd = UzpPassword;
#endif 

#if (!defined(DOS_FLX_H68_NLM_OS2_W32) && !defined(AMIGA) && !defined(RISCOS))
#if (!defined(MACOS) && !defined(ATARI) && !defined(VMS))
    G.echofd = -1;
#endif 
#endif 

#ifdef SYSTEM_SPECIFIC_CTOR
    SYSTEM_SPECIFIC_CTOR(__G);
#endif

#ifdef REENTRANT
#ifdef USETHREADID
    registerGlobalPointer(__G);
#else
    GG = &G;
#endif 
#endif 

    return &G;
}