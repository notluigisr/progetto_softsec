parse_ihu_subtlv(const unsigned char *a, int alen,
                 unsigned int *hello_send_us,
                 unsigned int *hello_rtt_receive_time)
{
    int type, len, i = 0, ret = 0;

    while(i < alen) {
        type = a[0];
        if(type == SUBTLV_PAD1) {
            i++;
            continue;
        }

        if(i + 1 > alen) {
            flog_err(EC_BABEL_PACKET,
		      "STR");
            return -1;
        }
        len = a[i + 1];
        if(i + len > alen) {
            flog_err(EC_BABEL_PACKET,
		      "STR");
            return -1;
        }

        if(type == SUBTLV_PADN) {
            
        } else if(type == SUBTLV_TIMESTAMP) {
            if(len >= 8) {
                DO_NTOHL(*hello_send_us, a + i + 2);
                DO_NTOHL(*hello_rtt_receive_time, a + i + 6);
                ret = 1;
            }
            else {
                flog_err(EC_BABEL_PACKET,
			  "STR");
            }
        } else {
            debugf(BABEL_DEBUG_COMMON,
                   "STR", type);
        }

        i += len + 2;
    }
    return ret;
}