GetNumSameData(const byte * curPtr, const int maxnum)
{
    int count = 1;

    if (1 == maxnum) {
        return (1);
    }
    while (*curPtr == *(curPtr + count) && maxnum > count) {
        count++;
    }

    return (count);
}