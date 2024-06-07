rsvg_new_use (void)
{
    RsvgNodeUse *use;
    use = g_new (RsvgNodeUse, 1);
    _rsvg_node_init (&use->super);
    use->super.draw = rsvg_node_use_draw;
    use->super.set_atts = rsvg_node_use_set_atts;
    use->x = _rsvg_css_parse_length ("STR");
    use->y = _rsvg_css_parse_length ("STR");
    use->w = _rsvg_css_parse_length ("STR");
    use->h = _rsvg_css_parse_length ("STR");
    use->link = NULL;
    return (RsvgNode *) use;
}