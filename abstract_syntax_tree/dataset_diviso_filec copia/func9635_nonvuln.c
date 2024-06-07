NOEXPORT int psk_compar(const void *a, const void *b) {
    PSK_KEYS *x=*(PSK_KEYS **)a, *y=*(PSK_KEYS **)b;

#if 0
    s_log(LOG_DEBUG, "STR", x->identity, y->identity);
#endif
    return strcmp(x->identity, y->identity);
}