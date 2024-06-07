static rfbCursorPtr rfbDefaultGetCursorPtr(rfbClientPtr cl)
{
   return(cl->screen->cursor);
}