int CJSON_CDECL main(void)
{
    UNITY_BEGIN();

    RUN_TEST(cjson_array_foreach_should_loop_over_arrays);
    RUN_TEST(cjson_array_foreach_should_not_dereference_null_pointer);
    RUN_TEST(cjson_get_object_item_should_get_object_items);
    RUN_TEST(cjson_get_object_item_case_sensitive_should_get_object_items);
    RUN_TEST(typecheck_functions_should_check_type);
    RUN_TEST(cjson_should_not_parse_to_deeply_nested_jsons);
    RUN_TEST(cjson_set_number_value_should_set_numbers);
    RUN_TEST(cjson_detach_item_via_pointer_should_detach_items);
    RUN_TEST(cjson_replace_item_via_pointer_should_replace_items);
    RUN_TEST(cjson_replace_item_in_object_should_preserve_name);
    RUN_TEST(cjson_functions_shouldnt_crash_with_null_pointers);
    RUN_TEST(ensure_should_fail_on_failed_realloc);
    RUN_TEST(skip_utf8_bom_should_skip_bom);
    RUN_TEST(skip_utf8_bom_should_not_skip_bom_if_not_at_beginning);
    RUN_TEST(cjson_get_string_value_should_get_a_string);
    RUN_TEST(cjson_create_string_reference_should_create_a_string_reference);
    RUN_TEST(cjson_create_object_reference_should_create_an_object_reference);
    RUN_TEST(cjson_create_array_reference_should_create_an_array_reference);
    RUN_TEST(cjson_add_item_to_object_should_not_use_after_free_when_string_is_aliased);

    return UNITY_END();
}