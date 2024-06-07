static void send_xembed_message(Display *display,
								Window   window,
								long     message,
								long     detail,
								long     data1,
								long     data2)
{
  XEvent xevent;
  memset(&xevent, 0, sizeof(xevent));
  xevent.xclient.window = window;
  xevent.xclient.type = ClientMessage;
  xevent.xclient.message_type = XInternAtom(display, "STR", False);
  xevent.xclient.format = 32;
  xevent.xclient.data.l[0] = CurrentTime; 
  xevent.xclient.data.l[1] = message;
  xevent.xclient.data.l[2] = detail;
  xevent.xclient.data.l[3] = data1;
  xevent.xclient.data.l[4] = data2;

  trap_errors();
  XSendEvent(display, xevent.xclient.window, False, NoEventMask, &xevent);
  XSync(display, False);
  untrap_errors();
}