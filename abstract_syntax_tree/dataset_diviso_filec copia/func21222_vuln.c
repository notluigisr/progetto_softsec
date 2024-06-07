send_parameters(struct iperf_test *test)
{
    int r = 0;
    cJSON *j;

    j = cJSON_CreateObject();
    if (j == NULL) {
	i_errno = IESENDPARAMS;
	r = -1;
    } else {
	if (test->protocol->id == Ptcp)
	    cJSON_AddTrueToObject(j, "STR");
	else if (test->protocol->id == Pudp)
	    cJSON_AddTrueToObject(j, "STR");
	cJSON_AddIntToObject(j, "STR", test->omit);
	if (test->server_affinity != -1)
	    cJSON_AddIntToObject(j, "STR", test->server_affinity);
	if (test->duration)
	    cJSON_AddIntToObject(j, "STR", test->duration);
	if (test->settings->bytes)
	    cJSON_AddIntToObject(j, "STR", test->settings->bytes);
	if (test->settings->blocks)
	    cJSON_AddIntToObject(j, "STR", test->settings->blocks);
	if (test->settings->mss)
	    cJSON_AddIntToObject(j, "STR", test->settings->mss);
	if (test->no_delay)
	    cJSON_AddTrueToObject(j, "STR");
	cJSON_AddIntToObject(j, "STR", test->num_streams);
	if (test->reverse)
	    cJSON_AddTrueToObject(j, "STR");
	if (test->settings->socket_bufsize)
	    cJSON_AddIntToObject(j, "STR", test->settings->socket_bufsize);
	if (test->settings->blksize)
	    cJSON_AddIntToObject(j, "STR", test->settings->blksize);
	if (test->settings->rate)
	    cJSON_AddIntToObject(j, "STR", test->settings->rate);
	if (test->settings->burst)
	    cJSON_AddIntToObject(j, "STR", test->settings->burst);
	if (test->settings->tos)
	    cJSON_AddIntToObject(j, "STR", test->settings->tos);
	if (test->settings->flowlabel)
	    cJSON_AddIntToObject(j, "STR", test->settings->flowlabel);
	if (test->title)
	    cJSON_AddStringToObject(j, "STR", test->title);
	if (test->congestion)
	    cJSON_AddStringToObject(j, "STR", test->congestion);
	if (test->get_server_output)
	    cJSON_AddIntToObject(j, "STR", iperf_get_test_get_server_output(test));

	if (test->debug) {
	    printf("STR", cJSON_Print(j));
	}

	if (JSON_write(test->ctrl_sck, j) < 0) {
	    i_errno = IESENDPARAMS;
	    r = -1;
	}
	cJSON_Delete(j);
    }
    return r;
}