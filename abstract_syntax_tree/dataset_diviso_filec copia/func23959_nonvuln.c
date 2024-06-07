static void kbd_leds(void *opaque, int ledstate)
{
    VncState *vs = opaque;
    int caps, num;

    caps = ledstate & QEMU_CAPS_LOCK_LED ? 1 : 0;
    num  = ledstate & QEMU_NUM_LOCK_LED  ? 1 : 0;

    if (vs->modifiers_state[0x3a] != caps) {
        vs->modifiers_state[0x3a] = caps;
    }
    if (vs->modifiers_state[0x45] != num) {
        vs->modifiers_state[0x45] = num;
    }
}