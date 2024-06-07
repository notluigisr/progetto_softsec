struct mbuf *dtom(Slirp *slirp, void *dat)
{
    struct mbuf *m;

    DEBUG_CALL("STR");
    DEBUG_ARG("STR", dat);

    
    for (m = (struct mbuf *)slirp->m_usedlist.qh_link;
         (struct quehead *)m != &slirp->m_usedlist; m = m->m_next) {
        if (m->m_flags & M_EXT) {
            if ((char *)dat >= m->m_ext && (char *)dat < (m->m_ext + m->m_size))
                return m;
        } else {
            if ((char *)dat >= m->m_dat && (char *)dat < (m->m_dat + m->m_size))
                return m;
        }
    }

    DEBUG_ERROR("STR");

    return (struct mbuf *)0;
}