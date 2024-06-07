void cpu_physical_memory_reset_dirty(ram_addr_t start, ram_addr_t length,
                                     unsigned client)
{
    if (length == 0)
        return;
    cpu_physical_memory_clear_dirty_range_type(start, length, client);

    if (tcg_enabled()) {
        tlb_reset_dirty_range_all(start, length);
    }
}