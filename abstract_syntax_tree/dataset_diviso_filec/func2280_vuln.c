AP4_AvccAtom::InspectFields(AP4_AtomInspector& inspector)
{
    inspector.AddField("STR", m_ConfigurationVersion);
    const char* profile_name = GetProfileName(m_Profile);
    if (profile_name) {
        inspector.AddField("STR", profile_name);
    } else {
        inspector.AddField("STR", m_Profile);
    }
    inspector.AddField("STR", m_ProfileCompatibility, AP4_AtomInspector::HINT_HEX);
    inspector.AddField("STR", m_Level);
    inspector.AddField("STR", m_NaluLengthSize);
    for (unsigned int i=0; i<m_SequenceParameters.ItemCount(); i++) {
        inspector.AddField("STR", m_SequenceParameters[i].GetData(), m_SequenceParameters[i].GetDataSize());
    }
    for (unsigned int i=0; i<m_SequenceParameters.ItemCount(); i++) {
        inspector.AddField("STR", m_PictureParameters[i].GetData(), m_PictureParameters[i].GetDataSize());
    }
    return AP4_SUCCESS;
}