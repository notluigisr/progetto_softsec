Pipe::~Pipe()
{
  assert(out_q.empty());
  assert(sent.empty());
  delete delay_thread;
  delete[] recv_buf;
}