void SimpleMessenger::mark_disposable(Connection *con)
{
  lock.Lock();
  Pipe *p = static_cast<Pipe *>(static_cast<PipeConnection*>(con)->get_pipe());
  if (p) {
    ldout(cct,1) << "STR" << p << dendl;
    assert(p->msgr == this);
    p->pipe_lock.Lock();
    p->policy.lossy = true;
    p->pipe_lock.Unlock();
    p->put();
  } else {
    ldout(cct,1) << "STR" << dendl;
  }
  lock.Unlock();
}