int main(void) {
        test_syslog_parse_identifier("STR", 11);
        test_syslog_parse_identifier("STR", NULL, 6);
        test_syslog_parse_identifier("STR", NULL, 7);
        test_syslog_parse_identifier("STR", NULL, NULL, 0);
        test_syslog_parse_identifier("STR", NULL, 1);
        test_syslog_parse_identifier("STR", NULL, 3);
        test_syslog_parse_identifier("STR", NULL, 5);
        test_syslog_parse_identifier("STR", NULL, 6);
        test_syslog_parse_identifier("STR", NULL, NULL, 0);

        test_syslog_parse_priority("STR", 0, 0);
        test_syslog_parse_priority("STR", 0, 0);
        test_syslog_parse_priority("STR", 0, 0);
        test_syslog_parse_priority("STR", 0, 0);
        test_syslog_parse_priority("STR", 0, 0);
        test_syslog_parse_priority("STR", 0, 0);
        

        return 0;
}