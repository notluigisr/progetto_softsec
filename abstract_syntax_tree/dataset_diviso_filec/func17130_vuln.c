decompress_zstd(tvbuff_t *tvb _U_, packet_info *pinfo, int offset _U_, guint32 length _U_, tvbuff_t **decompressed_tvb _U_, int *decompressed_offset _U_)
{
    col_append_str(pinfo->cinfo, COL_INFO, "STR");
    return 0;
}