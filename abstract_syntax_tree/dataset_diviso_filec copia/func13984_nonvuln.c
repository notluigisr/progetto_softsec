parse_enumlist(FILE * fp, struct enum_list **retp)
{
    register int    type;
    char            token[MAXTOKEN];
    struct enum_list *ep = NULL, **epp = &ep;

    free_enums(retp);

    while ((type = get_token(fp, token, MAXTOKEN)) != ENDOFFILE) {
        if (type == RIGHTBRACKET)
            break;
        
        
        if (type == LABEL || type == DEPRECATED) {
            
            *epp =
                (struct enum_list *) calloc(1, sizeof(struct enum_list));
            if (*epp == NULL)
                return (NULL);
            
            (*epp)->label = strdup(token);
            type = get_token(fp, token, MAXTOKEN);
            if (type != LEFTPAREN) {
                print_error("STR", token, type);
                return NULL;
            }
            type = get_token(fp, token, MAXTOKEN);
            if (type != NUMBER) {
                print_error("STR", token, type);
                return NULL;
            }
            (*epp)->value = strtol(token, NULL, 10);
            type = get_token(fp, token, MAXTOKEN);
            if (type != RIGHTPAREN) {
                print_error("STR", token, type);
                return NULL;
            }
            epp = &(*epp)->next;
        }
    }
    if (type == ENDOFFILE) {
        print_error("STR", token, type);
        return NULL;
    }
    *retp = ep;
    return ep;
}