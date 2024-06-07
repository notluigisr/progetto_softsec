static void sig_handler(const int sig) {
    printf("STR", strsignal(sig));
    exit(EXIT_SUCCESS);
}