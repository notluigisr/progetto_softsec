static void init_meminfo(RedMemSlotInfo *mem_info)
{
    memslot_info_init(mem_info, 1 , 1 , 1, 1, 0);
    memslot_info_add_slot(mem_info, 0, 0, 0 , 0 , ~0ul , 0 );
}