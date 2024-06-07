static void uuid_convert(uuid_t uuid)
{
    bswap32s((uint32_t *)&uuid[0]);
    bswap16s((uint16_t *)&uuid[4]);
    bswap16s((uint16_t *)&uuid[6]);
}