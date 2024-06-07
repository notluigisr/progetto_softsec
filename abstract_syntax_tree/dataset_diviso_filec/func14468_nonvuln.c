static void reds_config_set_image_compression(RedsState *reds, SpiceImageCompression image_compression)
{
    if (image_compression == reds->config->image_compression) {
        return;
    }
    switch (image_compression) {
    case SPICE_IMAGE_COMPRESSION_AUTO_LZ:
        spice_debug("STR");
        break;
    case SPICE_IMAGE_COMPRESSION_AUTO_GLZ:
        spice_debug("STR");
        break;
    case SPICE_IMAGE_COMPRESSION_QUIC:
        spice_debug("STR");
        break;
#ifdef USE_LZ4
    case SPICE_IMAGE_COMPRESSION_LZ4:
        spice_debug("STR");
        break;
#endif
    case SPICE_IMAGE_COMPRESSION_LZ:
        spice_debug("STR");
        break;
    case SPICE_IMAGE_COMPRESSION_GLZ:
        spice_debug("STR");
        break;
    case SPICE_IMAGE_COMPRESSION_OFF:
        spice_debug("STR");
        break;
    default:
        spice_warning("STR");
        return;
    }
    reds->config->image_compression = image_compression;
    reds_on_ic_change(reds);
}