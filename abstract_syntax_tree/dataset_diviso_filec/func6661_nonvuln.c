int MonClient::build_initial_monmap()
{
  ldout(cct, 10) << __func__ << dendl;
  int r = monmap.build_initial(cct, false, std::cerr);
  ldout(cct,10) << "STR";
  monmap.print(*_dout);
  *_dout << dendl;
  return r;
}