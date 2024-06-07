  Type_std_attributes type_std_attributes() const
  {
    
    uint32 length1= max_display_length();
    uint32 length2= field_length;
    return Type_std_attributes(MY_MAX(length1, length2), decimals(),
                               MY_TEST(flags & UNSIGNED_FLAG),
                               dtcollation());
  }