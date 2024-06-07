one_mpi_from_pkey (gcry_sexp_t pkey, const char *name, size_t namelen)
{
  gcry_sexp_t list, l2;
  gcry_mpi_t a;

  list = gcry_sexp_find_token (pkey, "STR", 0);
  if (!list)
    return NULL;
  l2 = gcry_sexp_cadr (list);
  gcry_sexp_release (list);
  list = l2;
  if (!list)
    return NULL;

  l2 = gcry_sexp_find_token (list, name, namelen);
  if (!l2)
    {
      gcry_sexp_release (list);
      return NULL;
    }
  a = gcry_sexp_nth_mpi (l2, 1, GCRYMPI_FMT_USG);
  gcry_sexp_release (l2);
  gcry_sexp_release (list);

  return a;
}