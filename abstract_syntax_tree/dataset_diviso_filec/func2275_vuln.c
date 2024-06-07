int main(void) {
        test_syslog_parse_identifier("STR", 11);
        test_syslog_parse_identifier("STR", NULL, 6);
        test_syslog_parse_identifier("STR", NULL, NULL, 0);

        return 0;
}