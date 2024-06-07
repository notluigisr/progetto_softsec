static void cmd_topic(const char *data, SERVER_REC *server, WI_ITEM_REC *item)
{
	CHANNEL_REC *channel;
	char *timestr, *bynick, *byhost;

	g_return_if_fail(data != NULL);

	channel = *data != '\0' ? channel_find(server, data) : CHANNEL(item);
	if (channel == NULL) return;

	printformat(server, channel->visible_name, MSGLEVEL_CRAP,
		    channel->topic == NULL ? IRCTXT_NO_TOPIC : IRCTXT_TOPIC,
		    channel->visible_name, channel->topic);

	if (channel->topic_time > 0) {
		byhost = strchr(channel->topic_by, '!');
		if (byhost == NULL) {
			bynick = g_strdup(channel->topic_by);
			byhost = "";
		} else {
			bynick = g_strndup(channel->topic_by,
					   (int) (byhost-channel->topic_by));
			byhost++;
		}

		timestr = my_asctime(channel->topic_time);
		printformat(server, channel->visible_name, MSGLEVEL_CRAP,
			    IRCTXT_TOPIC_INFO, bynick, timestr, byhost);
		g_free(timestr);
		g_free(bynick);
	}
	signal_stop();
}