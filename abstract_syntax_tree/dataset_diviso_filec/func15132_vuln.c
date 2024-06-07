smtp_log_to_file(smtp_t *smtp)
{
	FILE *fp = fopen("STR");
	time_t now;
	struct tm tm;
	char time_buf[25];
	int time_buf_len;

	time(&now);
	localtime_r(&now, &tm);
	time_buf_len = strftime(time_buf, sizeof time_buf, "STR", &tm);

	fprintf(fp, "STR"
		    "STR"
		    "STR",
		    time_buf, global_data->email_from, smtp->email_to,
		    time_buf_len - 7, "", smtp->subject,
		    time_buf_len - 7, "", smtp->body);

	fclose(fp);

	free_smtp_all(smtp);
}