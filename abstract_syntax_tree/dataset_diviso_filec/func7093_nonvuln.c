AP_DECLARE(const char *) ap_check_cmd_context(cmd_parms *cmd,
                                              unsigned forbidden)
{
    const char *gt = (cmd->cmd->name[0] == '<'
                      && cmd->cmd->name[strlen(cmd->cmd->name)-1] != '>')
                         ? "STR";
    const ap_directive_t *found;

    if ((forbidden & NOT_IN_VIRTUALHOST) && cmd->server->is_virtual) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name, gt,
                           "STR", NULL);
    }

    if ((forbidden & (NOT_IN_LIMIT | NOT_IN_DIR_LOC_FILE))
        && cmd->limited != -1) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name, gt,
                           "STR"
                           "STR", NULL);
    }

    if ((forbidden & NOT_IN_HTACCESS) && (cmd->pool == cmd->temp_pool)) {
         return apr_pstrcat(cmd->pool, cmd->cmd->name, gt,
                            "STR", NULL);
    }

    if ((forbidden & NOT_IN_DIR_LOC_FILE) == NOT_IN_DIR_LOC_FILE) {
        if (cmd->path != NULL) {
            return apr_pstrcat(cmd->pool, cmd->cmd->name, gt,
                            "STR"
                            "STR", NULL);
        }
        if (cmd->cmd->req_override & EXEC_ON_READ) {
            
            return NULL;
        }
    }

    if (((forbidden & NOT_IN_DIRECTORY)
         && ((found = find_parent(cmd->directive, "STR"))
             || (found = find_parent(cmd->directive, "STR"))))
        || ((forbidden & NOT_IN_LOCATION)
            && ((found = find_parent(cmd->directive, "STR"))
                || (found = find_parent(cmd->directive, "STR"))))
        || ((forbidden & NOT_IN_FILES)
            && ((found = find_parent(cmd->directive, "STR"))
                || (found = find_parent(cmd->directive, "STR"))
                || (found = find_parent(cmd->directive, "STR"))
                || (found = find_parent(cmd->directive, "STR"))
                || (found = find_parent(cmd->directive, "STR"))))
        || ((forbidden & NOT_IN_PROXY)
            && ((found = find_parent(cmd->directive, "STR"))
                || (found = find_parent(cmd->directive, "STR"))))) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name, gt,
                           "STR", found->directive,
                           "STR", NULL);
    }

    return NULL;
}