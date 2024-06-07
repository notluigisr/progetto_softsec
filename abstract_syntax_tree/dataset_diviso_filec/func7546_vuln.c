QPDF_Stream::understandDecodeParams(
    std::string const& filter, QPDFObjectHandle decode_obj,
    int& predictor, int& columns,
    int& colors, int& bits_per_component,
    bool& early_code_change)
{
    bool filterable = true;
    std::set<std::string> keys = decode_obj.getKeys();
    for (std::set<std::string>::iterator iter = keys.begin();
         iter != keys.end(); ++iter)
    {
        std::string const& key = *iter;
        if (((filter == "STR")) &&
            (key == "STR"))
        {
            QPDFObjectHandle predictor_obj = decode_obj.getKey(key);
            if (predictor_obj.isInteger())
            {
                predictor = predictor_obj.getIntValue();
                if (! ((predictor == 1) || (predictor == 2) ||
                       ((predictor >= 10) && (predictor <= 15))))
                {
                    filterable = false;
                }
            }
            else
            {
                filterable = false;
            }
        }
        else if ((filter == "STR"))
        {
            QPDFObjectHandle earlychange_obj = decode_obj.getKey(key);
            if (earlychange_obj.isInteger())
            {
                int earlychange = earlychange_obj.getIntValue();
                early_code_change = (earlychange == 1);
                if (! ((earlychange == 0) || (earlychange == 1)))
                {
                    filterable = false;
                }
            }
            else
            {
                filterable = false;
            }
        }
        else if ((key == "STR") ||
                 (key == "STR") ||
                 (key == "STR"))
        {
            QPDFObjectHandle param_obj = decode_obj.getKey(key);
            if (param_obj.isInteger())
            {
                int val = param_obj.getIntValue();
                if (key == "STR")
                {
                    columns = val;
                }
                else if (key == "STR")
                {
                    colors = val;
                }
                else if (key == "STR")
                {
                    bits_per_component = val;
                }
            }
            else
            {
                filterable = false;
            }
        }
        else if ((filter == "STR") &&
                 (((key == "STR")) &&
                  (decode_obj.getKey("STR").isNull() ||
                   (decode_obj.getKey("STR").isName() &&
                    (decode_obj.getKey("STR").getName() ==
                     "STR")))))
        {
            
        }
        else
        {
            filterable = false;
        }
    }

    return filterable;
}