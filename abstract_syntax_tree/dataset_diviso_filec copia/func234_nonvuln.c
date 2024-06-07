Perl_ck_warner_d(pTHX_ U32 err, const char* pat, ...)
{
    PERL_ARGS_ASSERT_CK_WARNER_D;

    if (Perl_ckwarn_d(aTHX_ err)) {
	va_list args;
	va_start(args, pat);
	vwarner(err, pat, &args);
	va_end(args);
    }
}