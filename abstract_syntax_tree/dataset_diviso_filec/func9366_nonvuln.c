parse_STACK_PUSH(char *arg, struct ofpbuf *ofpacts,
                 enum ofputil_protocol *usable_protocols OVS_UNUSED)
{
    return nxm_parse_stack_action(ofpact_put_STACK_PUSH(ofpacts), arg);
}