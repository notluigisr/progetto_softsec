autoar_extractor_check_file_conflict (GFile  *file,
                                      mode_t  extracted_filetype)
{
  GFileType file_type;

  file_type = g_file_query_file_type (file,
                                      G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                      NULL);
  
  if (file_type == G_FILE_TYPE_UNKNOWN) {
    return FALSE;
  }

  
  if (file_type == G_FILE_TYPE_DIRECTORY &&
      extracted_filetype == AE_IFDIR) {
    return FALSE;
  }

  return TRUE;
}