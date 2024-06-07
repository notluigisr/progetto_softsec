Perl_rsignal_state(pTHX_ int signo)
{
    dVAR;
    Sighandler_t oldsig;

#if defined(USE_ITHREADS) && !defined(WIN32)
    
    if (PL_curinterp != aTHX)
	return (Sighandler_t) SIG_ERR;
#endif

    PL_sig_trapped = 0;
    oldsig = PerlProc_signal(signo, sig_trap);
    PerlProc_signal(signo, oldsig);
    if (PL_sig_trapped)
	PerlProc_kill(PerlProc_getpid(), signo);
    return oldsig;
}