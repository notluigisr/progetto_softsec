parse_LEARN(char *arg, struct ofpbuf *ofpacts,
            enum ofputil_protocol *usable_protocols OVS_UNUSED)
{
    return learn_parse(arg, ofpacts);
}