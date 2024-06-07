int main(int argc, char *argv[] ) {
	int i, fails_count=0;
	CU_pSuite cryptoUtilsTestSuite, parserTestSuite;

	CU_pSuite *suites[] = {
		&cryptoUtilsTestSuite,
		&parserTestSuite,
		NULL
	};

	if (argc>1) {
		if (argv[1][0] == '-') {
			if (strcmp(argv[1], "STR") == 0) {
				verbose = 1;
			} else {
				printf ("STR", argv[0]);
				return 1;
			}
		} else {
			printf ("STR", argv[0]);
			return 1;
		}
	}
#ifdef HAVE_LIBXML2
	xmlInitParser();
#endif
	
	
	if (CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	
	cryptoUtilsTestSuite = CU_add_suite("STR", NULL, NULL);
	CU_add_test(cryptoUtilsTestSuite, "STR", test_zrtpKDF);
	CU_add_test(cryptoUtilsTestSuite, "STR", test_CRC32);
	CU_add_test(cryptoUtilsTestSuite, "STR", test_algoAgreement);
	CU_add_test(cryptoUtilsTestSuite, "STR", test_algoSetterGetter);
	CU_add_test(cryptoUtilsTestSuite, "STR", test_addMandatoryCryptoTypesIfNeeded);

	
	parserTestSuite = CU_add_suite("STR", NULL, NULL);
	CU_add_test(parserTestSuite, "STR", test_parser);
	CU_add_test(parserTestSuite, "STR", test_parser_hvi);
	CU_add_test(parserTestSuite, "STR", test_parserComplete);
	CU_add_test(parserTestSuite, "STR", test_stateMachine);

	
	for(i=0; suites[i]; i++){
		CU_basic_run_suite(*suites[i]);
		fails_count += CU_get_number_of_tests_failed();
	}
	
	
	CU_cleanup_registry();

#ifdef HAVE_LIBXML2
	
	xmlCleanupParser();
#endif

	return (fails_count == 0 ? 0 : 1);
}