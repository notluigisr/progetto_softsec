static const char* getenv_harder(pam_handle_t *handle, const char *key, const char *fallback) {
        const char *v;

        assert(handle);
        assert(key);

        

        v = pam_getenv(handle, key);
        if (!isempty(v))
                return v;

        v = getenv(key);
        if (!isempty(v))
                return v;

        return fallback;
}