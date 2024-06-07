irc_nick_free_all (struct t_irc_server *server, struct t_irc_channel *channel)
{
    if (!channel)
        return;

    
    while (channel->nicks)
    {
        irc_nick_free (server, channel, channel->nicks);
    }

    
    weechat_nicklist_remove_all (channel->buffer);

    
    channel->nicks_count = 0;
}