static void ext_key_event(VncState *vs, int down,
                          uint32_t sym, uint16_t keycode)
{
    
    if (keyboard_layout)
        key_event(vs, down, sym);
    else
        do_key_event(vs, down, keycode, sym);
}