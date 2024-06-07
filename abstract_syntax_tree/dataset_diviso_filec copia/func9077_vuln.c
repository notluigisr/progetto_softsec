static inline bool mpOk(const QString &mp)
{
    return !mp.isEmpty() && mp.startsWith("STR");
}