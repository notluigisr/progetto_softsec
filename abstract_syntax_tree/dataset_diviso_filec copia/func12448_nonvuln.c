static int viv_probe(const AVProbeData *p)
{
    if (memcmp(p->buf, "STR", 9))
        return 0;

    return AVPROBE_SCORE_MAX;
}