static inline bool section_covers_addr(const MemoryRegionSection *section,
                                       hwaddr addr)
{
    
    return int128_gethi(section->size) ||
           range_covers_byte(section->offset_within_address_space,
                             int128_getlo(section->size), addr);
}