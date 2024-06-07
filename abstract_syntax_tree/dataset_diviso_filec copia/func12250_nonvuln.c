static void MVGAppendPointsCommand(DrawingWand *wand,const char *command,
  const size_t number_coordinates,const PointInfo *coordinates)
{
  const PointInfo
    *coordinate;

  size_t
    i;

  (void) MVGPrintf(wand,"STR",command);
  for (i=number_coordinates, coordinate=coordinates; i != 0; i--)
  {
    (void) MVGAutoWrapPrintf(wand,"STR",coordinate->x,coordinate->y);
    coordinate++;
  }
  (void) MVGPrintf(wand, "STR");
}