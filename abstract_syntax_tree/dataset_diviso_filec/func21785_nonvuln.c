void restore_stdin(void)
{
#ifdef FIONBIO
    int nb = 0;

    ioctl(0, FIONBIO, &nb);
#else
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
#endif 
}