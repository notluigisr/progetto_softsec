void msg_init(void)
{
    usb_set_rx_callback(handle_usb_rx);
#if DEBUG_LINK
    usb_set_debug_rx_callback(handle_debug_usb_rx);
#endif
}