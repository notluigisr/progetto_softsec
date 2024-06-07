int VvcSliceHeader::deserialize(const VvcSpsUnit* sps, const VvcPpsUnit* pps)
{
    int rez = VvcUnit::deserialize();
    if (rez)
        return rez;

    try
    {
        if (m_reader.getBit())  
        {
            bool ph_gdr_or_irap_pic_flag = m_reader.getBit();
            m_reader.skipBit();  
            if (ph_gdr_or_irap_pic_flag)
                m_reader.skipBit();  
            if (m_reader.getBit())   
                m_reader.skipBit();  
            unsigned ph_pps_id = extractUEGolombCode();
            if (ph_pps_id > 63)
                return 1;
            pic_order_cnt_lsb = m_reader.getBits(sps->log2_max_pic_order_cnt_lsb);
            ;
        }

        return 0;
    }
    catch (VodCoreException& e)
    {
        return NOT_ENOUGH_BUFFER;
    }
}