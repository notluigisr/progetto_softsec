int linenoiseHistorySave(const char* filename) {
    FILE* fp = fopen(filename, "STR");
    if (fp == NULL) {
        return -1;
    }

    for (int j = 0; j < historyLen; ++j) {
        if (history[j][0] != '\0') {
            fprintf(fp, "STR", history[j]);
        }
    }
    fclose(fp);
    return 0;
}