static void reds_handle_sasl_result(void *opaque, RedSaslError status)
{
    RedLinkInfo *link = (RedLinkInfo *)opaque;

    switch (status) {
    case RED_SASL_ERROR_OK:
        reds_handle_link(link);
        break;
    case RED_SASL_ERROR_INVALID_DATA:
        reds_send_link_error(link, SPICE_LINK_ERR_INVALID_DATA);
        reds_link_free(link);
        break;
    default:
        
        
        
        reds_link_free(link);
        break;
    }
}