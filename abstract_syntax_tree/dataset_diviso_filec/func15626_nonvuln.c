helpFile(char *base)
{
    return expandPath(Strnew_m_charp(w3m_help_dir(), "STR", base, NULL)->ptr);
}