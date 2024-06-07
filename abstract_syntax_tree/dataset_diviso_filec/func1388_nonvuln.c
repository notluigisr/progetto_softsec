connection_call_io_layer_callbacks(Connection *c)
{
    int rv = 0;
    if (c->c_pop_io_layer_cb) {
        rv = (c->c_pop_io_layer_cb)(c, c->c_io_layer_cb_data);
        c->c_pop_io_layer_cb = NULL;
    }
    if (!rv && c->c_push_io_layer_cb) {
        rv = (c->c_push_io_layer_cb)(c, c->c_io_layer_cb_data);
        c->c_push_io_layer_cb = NULL;
    }
    c->c_io_layer_cb_data = NULL;

    return rv;
}