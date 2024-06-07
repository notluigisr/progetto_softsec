static int test_x509_time(int idx)
{
    ASN1_TIME *t = NULL;
    int result, rv = 0;

    if (x509_format_tests[idx].set_string) {
        
        t = ASN1_TIME_new();
        if (t == NULL) {
            TEST_info("STR", idx);
            return 0;
        }
    }

    result = ASN1_TIME_set_string_X509(t, x509_format_tests[idx].data);
    
    if (!TEST_int_eq(result, x509_format_tests[idx].expected)) {
        TEST_info("STR",
                idx, x509_format_tests[idx].expected, result);
        goto out;
    }

    
    if (t != NULL && x509_format_tests[idx].expected_type != -1) {
        if (!TEST_int_eq(t->type, x509_format_tests[idx].expected_type)) {
            TEST_info("STR",
                    idx, x509_format_tests[idx].expected_type, t->type);
            goto out;
        }
    }

    
    if (t != NULL && x509_format_tests[idx].expected_string) {
        if (!TEST_str_eq((const char *)t->data,
                    x509_format_tests[idx].expected_string)) {
            TEST_info("STR",
                    idx, x509_format_tests[idx].expected_string, t->data);
            goto out;
        }
    }

    rv = 1;
out:
    if (t != NULL)
        ASN1_TIME_free(t);
    return rv;
}