static void parseService4(const string &descr, ServiceTuple &st)
{
  vector<string>parts;
  stringtok(parts,descr,"STR");
  if(parts.empty())
    throw PDNSException("STR");
  st.host=parts[0];
  if(parts.size()>1)
    st.port=atoi(parts[1].c_str());
}