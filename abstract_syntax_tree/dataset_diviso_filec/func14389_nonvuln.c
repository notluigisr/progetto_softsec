static void vmxnet3_update_interrupt_line_state(VMXNET3State *s, int lidx)
{
    if (!s->interrupt_states[lidx].is_pending &&
       s->interrupt_states[lidx].is_asserted) {
        VMW_IRPRN("STR", lidx);
        _vmxnet3_deassert_interrupt_line(s, lidx);
        s->interrupt_states[lidx].is_asserted = false;
        return;
    }

    if (s->interrupt_states[lidx].is_pending &&
       !s->interrupt_states[lidx].is_masked &&
       !s->interrupt_states[lidx].is_asserted) {
        VMW_IRPRN("STR", lidx);
        s->interrupt_states[lidx].is_asserted =
            _vmxnet3_assert_interrupt_line(s, lidx);
        s->interrupt_states[lidx].is_pending = false;
        return;
    }
}