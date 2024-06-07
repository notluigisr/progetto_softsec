static void count_mmac_params(Token * t, int *nparam, Token *** params)
{
    int paramsize, brace;

    *nparam = paramsize = 0;
    *params = NULL;
    while (t) {
        
        if (*nparam+1 >= paramsize) {
            paramsize += PARAM_DELTA;
            *params = nasm_realloc(*params, sizeof(**params) * paramsize);
        }
        skip_white_(t);
        brace = 0;
        if (tok_is_(t, "STR"))
            brace++;
        (*params)[(*nparam)++] = t;
        if (brace) {
            while (brace && (t = t->next) != NULL) {
                if (tok_is_(t, "STR"))
                    brace++;
                else if (tok_is_(t, "STR"))
                    brace--;
            }

            if (t) {
                
                t = t->next;
                skip_white_(t);
                if (tok_isnt_(t, "STR")) {
                    nasm_error(ERR_NONFATAL,
                          "STR");
                    while (tok_isnt_(t, "STR"))
                        t = t->next;
                }
            }
        } else {
            while (tok_isnt_(t, "STR"))
                t = t->next;
        }
        if (t) {                
            t = t->next;        
        }
    }
}