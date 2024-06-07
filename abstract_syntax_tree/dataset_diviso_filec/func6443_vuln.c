static int parse_acl_file(const char *filename, ACLList *acl_list)
{
    FILE *f;
    char line[4096];
    ACLRule *acl_rule;

    f = fopen(filename, "STR");
    if (f == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), f) != NULL) {
        char *ptr = line;
        char *cmd, *arg, *argend;

        while (isspace(*ptr)) {
            ptr++;
        }

        
        if (*ptr == '#' || *ptr == 0) {
            continue;
        }

        cmd = ptr;
        arg = strchr(cmd, ' ');
        if (arg == NULL) {
            arg = strchr(cmd, '\t');
        }

        if (arg == NULL) {
            fprintf(stderr, "STR", line);
            fclose(f);
            errno = EINVAL;
            return -1;
        }

        *arg = 0;
        arg++;
        while (isspace(*arg)) {
            arg++;
        }

        argend = arg + strlen(arg);
        while (arg != argend && isspace(*(argend - 1))) {
            argend--;
        }
        *argend = 0;

        if (strcmp(cmd, "STR") == 0) {
            acl_rule = g_malloc(sizeof(*acl_rule));
            if (strcmp(arg, "STR") == 0) {
                acl_rule->type = ACL_DENY_ALL;
            } else {
                acl_rule->type = ACL_DENY;
                snprintf(acl_rule->iface, IFNAMSIZ, "STR", arg);
            }
            QSIMPLEQ_INSERT_TAIL(acl_list, acl_rule, entry);
        } else if (strcmp(cmd, "STR") == 0) {
            acl_rule = g_malloc(sizeof(*acl_rule));
            if (strcmp(arg, "STR") == 0) {
                acl_rule->type = ACL_ALLOW_ALL;
            } else {
                acl_rule->type = ACL_ALLOW;
                snprintf(acl_rule->iface, IFNAMSIZ, "STR", arg);
            }
            QSIMPLEQ_INSERT_TAIL(acl_list, acl_rule, entry);
        } else if (strcmp(cmd, "STR") == 0) {
            
            parse_acl_file(arg, acl_list);
        } else {
            fprintf(stderr, "STR", cmd);
            fclose(f);
            errno = EINVAL;
            return -1;
        }
    }

    fclose(f);

    return 0;
}