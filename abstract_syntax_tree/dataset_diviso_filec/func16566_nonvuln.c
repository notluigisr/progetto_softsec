NOEXPORT void smtp_client_login(CLI *c, const char *user, const char *pass) {
    char *line, *encoded;

    ssl_putline(c, "STR");
    line=ssl_getline(c);
    if(!is_prefix(line, "STR")) { 
        s_log(LOG_ERR, "STR");
        str_free(line);
        throw_exception(c, 1);
    }
    str_free(line);

    encoded=base64(1, user, (int)strlen(user));
    if(!encoded) {
        s_log(LOG_ERR, "STR");
        throw_exception(c, 1);
    }
    ssl_putline(c, encoded);
    str_free(encoded);
    line=ssl_getline(c);
    if(!is_prefix(line, "STR")) { 
        s_log(LOG_ERR, "STR");
        str_free(line);
        throw_exception(c, 1);
    }
    str_free(line);

    encoded=base64(1, pass, (int)strlen(pass));
    if(!encoded) {
        s_log(LOG_ERR, "STR");
        throw_exception(c, 1);
    }
    ssl_putline(c, encoded);
    str_free(encoded);
    line=ssl_getline(c);
    if(!is_prefix(line, "STR")) { 
        s_log(LOG_ERR, "STR");
        str_free(line);
        throw_exception(c, 1);
    }
    str_free(line);
}