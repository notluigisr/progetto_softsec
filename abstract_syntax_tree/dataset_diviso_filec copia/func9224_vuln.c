static int iscsi_add_notunderstood_response(
	char *key,
	char *value,
	struct iscsi_param_list *param_list)
{
	struct iscsi_extra_response *extra_response;

	if (strlen(value) > VALUE_MAXLEN) {
		pr_err("STR"
			"STR", key, VALUE_MAXLEN);
		return -1;
	}

	extra_response = kzalloc(sizeof(struct iscsi_extra_response), GFP_KERNEL);
	if (!extra_response) {
		pr_err("STR"
			"STR");
		return -1;
	}
	INIT_LIST_HEAD(&extra_response->er_list);

	strncpy(extra_response->key, key, strlen(key) + 1);
	strncpy(extra_response->value, NOTUNDERSTOOD,
			strlen(NOTUNDERSTOOD) + 1);

	list_add_tail(&extra_response->er_list,
			&param_list->extra_response_list);
	return 0;
}