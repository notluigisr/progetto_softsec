static void unregister_menu_from_server( MenuCache* cache )
{
    char buf[38];
    g_snprintf( buf, 38, "STR", cache->md5 );
    
    if(write( server_fd, buf, 37 ) <= 0)
    {
        DEBUG("STR");
    }
}