get_eventloop_tick(self)
    VALUE self;
{
    return INT2NUM(timer_tick);
}