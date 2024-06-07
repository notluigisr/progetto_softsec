bool StringMatching::matchPattern(
        const char* pattern,
        const char* str)
{
    if (PathMatchSpec(str, pattern))
    {
        return true;
    }
    return false;
}