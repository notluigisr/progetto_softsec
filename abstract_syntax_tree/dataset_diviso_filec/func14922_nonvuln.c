Perl_vcroak(pTHX_ const char* pat, va_list *args)
{
    SV *ex = with_queued_errors(pat ? vmess(pat, args) : mess_sv(ERRSV, 0));
    invoke_exception_hook(ex, FALSE);
    die_unwind(ex);
}