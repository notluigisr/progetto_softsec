etcFile(char *base)
{
    return expandPath(Strnew_m_charp(w3m_etc_dir(), "STR", base, NULL)->ptr);
}