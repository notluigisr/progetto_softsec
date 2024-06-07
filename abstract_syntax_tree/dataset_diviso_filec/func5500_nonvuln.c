static void bmdma_set_inactive(IDEDMA *dma, bool more)
{
    BMDMAState *bm = DO_UPCAST(BMDMAState, dma, dma);

    bm->dma_cb = NULL;
    bm->unit = -1;
    if (more) {
        bm->status |= BM_STATUS_DMAING;
    } else {
        bm->status &= ~BM_STATUS_DMAING;
    }
}