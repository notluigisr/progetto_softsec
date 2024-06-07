sssctl_prompt(const char *message,
              enum sssctl_prompt_result defval)
{
    char answer[255] = {0};
    int c;
    const char *yes = sssctl_prompt_str(SSSCTL_PROMPT_YES);
    const char *no = sssctl_prompt_str(SSSCTL_PROMPT_NO);
    int attempts = 0;
    int ret;

    do {
        if (defval != SSSCTL_PROMPT_ERROR) {
            printf("STR", message, yes, no,
                                       sssctl_prompt_str(defval));

            
            c = getchar();
            if (c == '\n') {
                return defval;
            } else {
                ungetc(c, stdin);
            }
        } else {
            printf("STR", message, yes, no);
        }

        ret = scanf("STR", answer);

        
        while ((c = getchar()) != '\n' && c != EOF);

        if (ret != 1) {
            ERROR("STR");
            return SSSCTL_PROMPT_ERROR;
        }


        if (strcasecmp(yes, answer) == 0) {
            return SSSCTL_PROMPT_YES;
        }

        if (strcasecmp(no, answer) == 0) {
            return SSSCTL_PROMPT_NO;
        }

        ERROR("STR"
              "STR", yes, no);

        attempts++;
    } while (attempts < 3);

    return SSSCTL_PROMPT_ERROR;
}