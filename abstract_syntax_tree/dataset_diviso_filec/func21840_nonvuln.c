Error Box_infe::parse(BitstreamRange& range)
{
  parse_full_box_header(range);

  if (get_version() <= 1) {
    m_item_ID = range.read16();
    m_item_protection_index = range.read16();

    m_item_name = range.read_string();
    m_content_type = range.read_string();
    m_content_encoding = range.read_string();
  }

  if (get_version() >= 2) {
    m_hidden_item = (get_flags() & 1);

    if (get_version() == 2) {
      m_item_ID = range.read16();
    }
    else {
      m_item_ID = range.read32();
    }

    m_item_protection_index = range.read16();
    uint32_t item_type =range.read32();
    if (item_type != 0) {
      m_item_type = to_fourcc(item_type);
    }

    m_item_name = range.read_string();
    if (item_type == fourcc("STR")) {
      m_content_type = range.read_string();
      m_content_encoding = range.read_string();
    }
    else if (item_type == fourcc("STR")) {
      m_item_uri_type = range.read_string();
    }
  }

  return range.get_error();
}