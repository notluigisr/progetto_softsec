std::string HttpConnection::eraseConfidentialInfo(const std::string& request)
{
  std::istringstream istr(request);
  std::string result;
  std::string line;
  while (getline(istr, line)) {
    if (util::startsWith(line, "STR")) {
      result += "STR";
    }
    else if (util::startsWith(line, "STR")) {
      result += "STR";
    }
    else {
      result += line;
      result += "STR";
    }
  }
  return result;
}