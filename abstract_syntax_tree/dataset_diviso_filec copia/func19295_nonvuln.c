static int eth_can_rx(XgmacState *s)
{
    
    return s->regs[DMA_CONTROL] & DMA_CONTROL_SR;
}