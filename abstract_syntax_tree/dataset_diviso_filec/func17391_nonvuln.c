void sdsclear(sds s) {
    sdssetlen(s, 0);
    s[0] = '\0';
}