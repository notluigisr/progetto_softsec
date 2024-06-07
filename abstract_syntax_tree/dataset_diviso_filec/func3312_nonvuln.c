PJ_DEF(pj_ssize_t) pjmedia_wav_player_get_len(pjmedia_port *port)
{
    struct file_reader_port *fport;
    pj_ssize_t size;

    
    PJ_ASSERT_RETURN(port, -PJ_EINVAL);

    
    PJ_ASSERT_RETURN(port->info.signature == SIGNATURE, -PJ_EINVALIDOP);

    fport = (struct file_reader_port*) port;

    size = (pj_ssize_t) fport->fsize;
    return size - fport->start_data;
}