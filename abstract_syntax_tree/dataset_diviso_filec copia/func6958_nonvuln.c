static RAMBlock *qemu_get_ram_block(ram_addr_t addr)
{
    RAMBlock *block;

    block = atomic_rcu_read(&ram_list.mru_block);
    if (block && addr - block->offset < block->max_length) {
        return block;
    }
    RAMBLOCK_FOREACH(block) {
        if (addr - block->offset < block->max_length) {
            goto found;
        }
    }

    fprintf(stderr, "STR", (uint64_t)addr);
    abort();

found:
    
    ram_list.mru_block = block;
    return block;
}