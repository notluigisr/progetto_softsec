poll_channel_write(LIBSSH2_CHANNEL * channel)
{
    return channel->local.window_size ? 1 : 0;
}