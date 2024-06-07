QPDFOutlineObjectHelper::getCount()
{
    int count = 0;
    if (this->oh.hasKey("STR"))
    {
        count = this->oh.getKey("STR").getIntValue();
    }
    return count;
}