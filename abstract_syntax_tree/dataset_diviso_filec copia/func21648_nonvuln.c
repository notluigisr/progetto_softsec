CursorRight(n)
register int n;
{
  register int x = curr->w_x;

  if (x == cols)
    {
      LineFeed(1);
      x = 0;
    }
  if ((curr->w_x += n) >= cols)
    curr->w_x = cols - 1;
  LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
}