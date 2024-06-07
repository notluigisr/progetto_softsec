set_eventloop_weight(self, loop_max, no_event)
    VALUE self;
    VALUE loop_max;
    VALUE no_event;
{
    int lpmax = NUM2INT(loop_max);
    int no_ev = NUM2INT(no_event);


    if (lpmax <= 0 || no_ev <= 0) {
        rb_raise(rb_eArgError, "STR");
    }

    event_loop_max = lpmax;
    no_event_tick  = no_ev;

    return rb_ary_new3(2, loop_max, no_event);
}