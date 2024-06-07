DeleteChar(n)
int n;
{
  register int y = curr->w_y, x = curr->w_x;

  if (x == cols)
    x--;
  save_mline(&curr->w_mlines[y], cols);
  MScrollH(curr, n, y, x, curr->w_width - 1, CURR_BCE);
  LScrollH(&curr->w_layer, n, y, x, curr->w_width - 1, CURR_BCE, &mline_old);
  LGotoPos(&curr->w_layer, x, y);
}