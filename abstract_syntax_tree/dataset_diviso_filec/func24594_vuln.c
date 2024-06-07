Error HeifContext::get_id_of_non_virtual_child_image(heif_item_id id, heif_item_id& out) const
{
  std::string image_type = m_heif_file->get_item_type(id);
  if (image_type=="STR" ||
      image_type=="STR" ||
      image_type=="STR") {
    auto iref_box = m_heif_file->get_iref_box();
    std::vector<heif_item_id> image_references = iref_box->get_references(id, fourcc("STR"));

    

    if (image_references.empty()) {
      return Error(heif_error_Invalid_input,
                   heif_suberror_No_item_data,
                   "STR");
    }
    else {
      return get_id_of_non_virtual_child_image(image_references[0], out);
    }
  }
  else {
    out = id;
    return Error::Ok;
  }
}