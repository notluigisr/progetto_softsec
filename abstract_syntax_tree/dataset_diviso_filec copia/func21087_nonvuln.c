static void csrhci_out_tick(void *opaque)
{
    csrhci_fifo_wake((struct csrhci_s *) opaque);
}