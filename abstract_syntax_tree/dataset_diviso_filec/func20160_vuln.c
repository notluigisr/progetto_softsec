static void fdctrl_write_data(FDCtrl *fdctrl, uint32_t value)
{
    FDrive *cur_drv;
    int pos;

    
    if (!(fdctrl->dor & FD_DOR_nRESET)) {
        FLOPPY_DPRINTF("STR");
        return;
    }
    if (!(fdctrl->msr & FD_MSR_RQM) || (fdctrl->msr & FD_MSR_DIO)) {
        FLOPPY_DPRINTF("STR");
        return;
    }
    fdctrl->dsr &= ~FD_DSR_PWRDOWN;
    
    if (fdctrl->msr & FD_MSR_NONDMA) {
        
        pos = fdctrl->data_pos++;
        pos %= FD_SECTOR_LEN;
        fdctrl->fifo[pos] = value;
        if (pos == FD_SECTOR_LEN - 1 ||
            fdctrl->data_pos == fdctrl->data_len) {
            cur_drv = get_cur_drv(fdctrl);
            if (blk_write(cur_drv->blk, fd_sector(cur_drv), fdctrl->fifo, 1)
                < 0) {
                FLOPPY_DPRINTF("STR",
                               fd_sector(cur_drv));
                return;
            }
            if (!fdctrl_seek_to_next_sect(fdctrl, cur_drv)) {
                FLOPPY_DPRINTF("STR",
                               fd_sector(cur_drv));
                return;
            }
        }
        
        if (fdctrl->data_pos == fdctrl->data_len)
            fdctrl_stop_transfer(fdctrl, 0x00, 0x00, 0x00);
        return;
    }
    if (fdctrl->data_pos == 0) {
        
        pos = command_to_handler[value & 0xff];
        FLOPPY_DPRINTF("STR", handlers[pos].name);
        fdctrl->data_len = handlers[pos].parameters + 1;
        fdctrl->msr |= FD_MSR_CMDBUSY;
    }

    FLOPPY_DPRINTF("STR", __func__, value);
    fdctrl->fifo[fdctrl->data_pos++] = value;
    if (fdctrl->data_pos == fdctrl->data_len) {
        
        if (fdctrl->data_state & FD_STATE_FORMAT) {
            fdctrl_format_sector(fdctrl);
            return;
        }

        pos = command_to_handler[fdctrl->fifo[0] & 0xff];
        FLOPPY_DPRINTF("STR", handlers[pos].name);
        (*handlers[pos].handler)(fdctrl, handlers[pos].direction);
    }
}