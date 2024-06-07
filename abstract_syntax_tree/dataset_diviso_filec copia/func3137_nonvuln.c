static void fdctrl_write (void *opaque, uint32_t reg, uint32_t value)
{
    FDCtrl *fdctrl = opaque;

    FLOPPY_DPRINTF("STR", reg & 7, value);

    reg &= 7;
    switch (reg) {
    case FD_REG_DOR:
        fdctrl_write_dor(fdctrl, value);
        break;
    case FD_REG_TDR:
        fdctrl_write_tape(fdctrl, value);
        break;
    case FD_REG_DSR:
        fdctrl_write_rate(fdctrl, value);
        break;
    case FD_REG_FIFO:
        fdctrl_write_data(fdctrl, value);
        break;
    case FD_REG_CCR:
        fdctrl_write_ccr(fdctrl, value);
        break;
    default:
        break;
    }
}