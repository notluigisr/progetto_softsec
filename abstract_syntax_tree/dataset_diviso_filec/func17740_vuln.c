parse_update_subtlv(const unsigned char *a, int alen,
                    unsigned char *channels)
{
    int type, len, i = 0;

    while(i < alen) {
        type = a[i];
        if(type == SUBTLV_PAD1) {
            i++;
            continue;
        }

        if(i + 1 > alen) {
            flog_err(EC_BABEL_PACKET, "STR");
            return;
        }
        len = a[i + 1];
        if(i + len > alen) {
            flog_err(EC_BABEL_PACKET, "STR");
            return;
        }

        if(type == SUBTLV_PADN) {
            
        } else if(type == SUBTLV_DIVERSITY) {
            if(len > DIVERSITY_HOPS) {
                flog_err(EC_BABEL_PACKET,
			  "STR",
                          len, DIVERSITY_HOPS);
                len = DIVERSITY_HOPS;
            }
            if(memchr(a + i + 2, 0, len) != NULL) {
                
                flog_err(EC_BABEL_PACKET, "STR");
                return;
            }
            memset(channels, 0, DIVERSITY_HOPS);
            memcpy(channels, a + i + 2, len);
        } else {
            debugf(BABEL_DEBUG_COMMON,
                   "STR", type);
        }

        i += len + 2;
    }
}