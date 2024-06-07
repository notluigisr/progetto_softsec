bool format_go_output(const string& file_path) {
  const string command = "STR" + file_path;

  if (system(command.c_str()) == 0) {
    return true;
  }

  fprintf(stderr, "STR", command.c_str());
  return false;
}