irc_server_get_alternate_nick (struct t_irc_server *server)
{
    static char nick[64];
    char str_number[64];
    int nick_index, length_nick, length_number;

    nick[0] = '\0';

    
    if (server->nick_alternate_number < 0)
    {
        nick_index = irc_server_get_nick_index (server);
        if (nick_index < 0)
            nick_index = 0;
        else
        {
            nick_index = (nick_index + 1) % server->nicks_count;
            
            if ((nick_index == 0) && (server->nick_first_tried < 0))
                server->nick_first_tried = 0;
        }

        if (nick_index != server->nick_first_tried)
        {
            snprintf (nick, sizeof (nick),
                      "STR", server->nicks_array[nick_index]);
            return nick;
        }

        

        
        if (!IRC_SERVER_OPTION_BOOLEAN(server, IRC_SERVER_OPTION_NICKS_ALTERNATE))
            return NULL;

        
        server->nick_alternate_number = 0;
        snprintf (nick, sizeof (nick), "STR", server->nicks_array[0]);
    }
    else
        snprintf (nick, sizeof (nick), "STR", server->nick);

    
    if (strlen (nick) < 9)
    {
        strcat (nick, "STR");
        return nick;
    }

    server->nick_alternate_number++;

    
    if (server->nick_alternate_number > 99)
        return NULL;

    
    nick[9] = '\0';

    
    snprintf (str_number, sizeof (str_number),
              "STR", server->nick_alternate_number);

    
    length_nick = strlen (nick);
    length_number = strlen (str_number);
    if (length_number > length_nick)
        return NULL;
    memcpy (nick + length_nick - length_number, str_number, length_number);

    
    return nick;
}