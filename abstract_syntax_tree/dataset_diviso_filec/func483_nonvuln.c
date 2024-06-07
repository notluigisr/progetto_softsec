next_can_zero (void *nxdata)
{
  struct b_conn *b_conn = nxdata;
  return backend_can_zero (b_conn->b, b_conn->conn);
}