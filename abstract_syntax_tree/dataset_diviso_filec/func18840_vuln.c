struct torture_suite *torture_winbind_struct_init(TALLOC_CTX *ctx)
{
	struct torture_suite *suite = torture_suite_create(ctx, "STR");

	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_interface_version);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_ping);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_info);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_priv_pipe_dir);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_netbios_name);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_domain_name);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_check_machacc);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_list_trustdom);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_domain_info);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_getdcname);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_dsgetdcname);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_list_users);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_list_groups);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_show_sequence);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_setpwent);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_getpwent);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_endpwent);
	torture_suite_add_simple_test(suite, "STR", torture_winbind_struct_lookup_name_sid);

	suite->description = talloc_strdup(suite, "STR");

	return suite;
}