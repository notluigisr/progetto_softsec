static bool ide_bmdma_status_needed(void *opaque)
{
    BMDMAState *bm = opaque;

    
    uint8_t abused_bits = BM_MIGRATION_COMPAT_STATUS_BITS;

    return ((bm->status & abused_bits) != 0);
}