win_comp_pos(void)
{
    int		row = tabline_height();
    int		col = 0;

    frame_comp_pos(topframe, &row, &col);
    return row;
}