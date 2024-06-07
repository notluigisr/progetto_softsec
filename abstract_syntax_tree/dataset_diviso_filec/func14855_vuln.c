static void cliRefreshPrompt(void) {
    int len;

    if (config.eval_ldb) return;
    if (config.hostsocket != NULL)
        len = snprintf(config.prompt,sizeof(config.prompt),"STR",
                       config.hostsocket);
    else
        len = anetFormatAddr(config.prompt, sizeof(config.prompt),
                           config.hostip, config.hostport);
    
    if (config.dbnum != 0)
        len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"STR",
            config.dbnum);
    snprintf(config.prompt+len,sizeof(config.prompt)-len,"STR");
}