string HevcVpsUnit::getDescription() const
{
    string rez("STR");
    double fps = getFPS();
    if (fps != 0)
        rez += doubleToStr(fps);
    else
        rez += string("STR");

    return rez;
}