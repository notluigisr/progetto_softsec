Error Box_idat::read_data(std::shared_ptr<StreamReader> istr,
                          uint64_t start, uint64_t length,
                          std::vector<uint8_t>& out_data) const
{
  

  auto curr_size = out_data.size();

  if (MAX_MEMORY_BLOCK_SIZE - curr_size < length) {
    std::stringstream sstr;
    sstr << "STR"
         << (curr_size + length) << "STR"
         << MAX_MEMORY_BLOCK_SIZE << "STR";

    return Error(heif_error_Memory_allocation_error,
                 heif_suberror_Security_limit_exceeded,
                 sstr.str());
  }


  
  if (start > (uint64_t)m_data_start_pos + get_box_size()) {
    return Error(heif_error_Invalid_input,
                 heif_suberror_End_of_data);
  } else if (length > get_box_size() || start + length > get_box_size()) {
    return Error(heif_error_Invalid_input,
                 heif_suberror_End_of_data);
  }

  StreamReader::grow_status status = istr->wait_for_file_size((int64_t)m_data_start_pos + start + length);
  if (status == StreamReader::size_beyond_eof ||
      status == StreamReader::timeout) {
    
    return Error(heif_error_Invalid_input,
                 heif_suberror_End_of_data);
  }

  bool success;
  success = istr->seek(m_data_start_pos + (std::streampos)start);
  assert(success);
  (void)success;

  

  out_data.resize(static_cast<size_t>(curr_size + length));
  uint8_t* data = &out_data[curr_size];

  success = istr->read((char*)data, static_cast<size_t>(length));
  assert(success);

  return Error::Ok;
}