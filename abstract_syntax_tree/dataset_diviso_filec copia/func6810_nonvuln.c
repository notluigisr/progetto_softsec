gs_heap_resize_string(gs_memory_t * mem, byte * data, uint old_num, uint new_num,
                      client_name_t cname)
{
    if (gs_heap_object_type(mem, data) != &st_bytes)
        lprintf2("STR",
                 client_name_string(cname), (ulong) data);
    return gs_heap_resize_object(mem, data, new_num, cname);
}