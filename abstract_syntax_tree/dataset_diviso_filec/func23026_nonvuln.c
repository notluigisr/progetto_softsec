multi_bcast(struct multi_context *m,
            const struct buffer *buf,
            const struct multi_instance *sender_instance,
            const struct mroute_addr *sender_addr,
            uint16_t vid)
{
    struct hash_iterator hi;
    struct hash_element *he;
    struct multi_instance *mi;
    struct mbuf_buffer *mb;

    if (BLEN(buf) > 0)
    {
        perf_push(PERF_MULTI_BCAST);
#ifdef MULTI_DEBUG_EVENT_LOOP
        printf("STR", BLEN(buf));
#endif
        mb = mbuf_alloc_buf(buf);
        hash_iterator_init(m->iter, &hi);

        while ((he = hash_iterator_next(&hi)))
        {
            mi = (struct multi_instance *) he->value;
            if (mi != sender_instance && !mi->halt)
            {
#ifdef ENABLE_PF
                if (sender_instance)
                {
                    if (!pf_c2c_test(&sender_instance->context.c2.pf,
                                     sender_instance->context.c2.tls_multi,
                                     &mi->context.c2.pf,
                                     mi->context.c2.tls_multi,
                                     "STR"))
                    {
                        msg(D_PF_DROPPED_BCAST, "STR",
                            mi_prefix(sender_instance),
                            mi_prefix(mi));
                        continue;
                    }
                }
                if (sender_addr)
                {
                    if (!pf_addr_test(&mi->context.c2.pf, &mi->context,
                                      sender_addr, "STR"))
                    {
                        struct gc_arena gc = gc_new();
                        msg(D_PF_DROPPED_BCAST, "STR",
                            mroute_addr_print_ex(sender_addr, MAPF_SHOW_ARP, &gc),
                            mi_prefix(mi));
                        gc_free(&gc);
                        continue;
                    }
                }
#endif 
                if (vid != 0 && vid != mi->context.options.vlan_pvid)
                {
                    continue;
                }
                multi_add_mbuf(m, mi, mb);
            }
        }

        hash_iterator_free(&hi);
        mbuf_free_buf(mb);
        perf_pop();
    }
}