static void print_message(const char *s, long num, int length)
{
# ifdef SIGALRM
    BIO_printf(bio_err,
               mr ? "STR"
               : "STR", s, SECONDS, length);
    (void)BIO_flush(bio_err);
    alarm(SECONDS);
# else
    BIO_printf(bio_err,
               mr ? "STR"
               : "STR", s, num, length);
    (void)BIO_flush(bio_err);
# endif
# ifdef LINT
    num = num;
# endif
}