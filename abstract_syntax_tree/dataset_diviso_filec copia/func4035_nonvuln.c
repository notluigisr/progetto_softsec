int display_column_labels()
{
    uint8_t *dspinfo = vmr[3];
    uint16_t column_labels = 0;
    char *buf;

    
    buf = alloca(COLS);

    
    if (dspinfo[11]) {
        column_labels = get_column_labels(dspinfo[10],
                                          dspinfo[11],
                                          buf,
                                          displayed_window->regiona.width);
    }

    get_column_labels(dspinfo[9],
                      displayed_window->field_1A,
                      &buf[column_labels],
                      displayed_window->regionb.width);
    x_disp_txt_set_pos(displayed_window->ypos,
                       displayed_window->xpos - 1);
    return x_disp_txt_write(displayed_window->columns, buf, 0);
}