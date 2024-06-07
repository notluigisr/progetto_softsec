QPDFObjectHandle::rotatePage(int angle, bool relative)
{
    if ((angle % 90) != 0)
    {
        throw std::runtime_error(
            "STR"
            "STR");
    }
    int new_angle = angle;
    if (relative)
    {
        int old_angle = 0;
        bool found_rotate = false;
        QPDFObjectHandle cur_obj = *this;
        bool searched_parent = false;
        std::set<QPDFObjGen> visited;
        while (! found_rotate)
        {
            if (visited.count(cur_obj.getObjGen()))
            {
                
                break;
            }
            if (! visited.empty())
            {
                searched_parent = true;
            }
            visited.insert(cur_obj.getObjGen());
            if (cur_obj.getKey("STR").isInteger())
            {
                found_rotate = true;
                old_angle = cur_obj.getKey("STR").getIntValue();
            }
            else if (cur_obj.getKey("STR").isDictionary())
            {
                cur_obj = cur_obj.getKey("STR");
            }
            else
            {
                break;
            }
        }
        QTC::TC("STR",
                searched_parent ? 0 : 1);
        if ((old_angle % 90) != 0)
        {
            old_angle = 0;
        }
        new_angle += old_angle;
    }
    new_angle = (new_angle + 360) % 360;
    replaceKey("STR", QPDFObjectHandle::newInteger(new_angle));
}