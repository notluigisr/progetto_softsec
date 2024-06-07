int mutt_copy_body (FILE *fp, BODY **tgt, BODY *src)
{
  char tmp[_POSIX_PATH_MAX];
  BODY *b;

  PARAMETER *par, **ppar;
  
  short use_disp;

  if (src->filename)
  {
    use_disp = 1;
    strfcpy (tmp, src->filename, sizeof (tmp));
  }
  else
  {
    use_disp = 0;
    tmp[0] = '\0';
  }

  mutt_adv_mktemp (tmp, sizeof (tmp));
  if (mutt_save_attachment (fp, src, tmp, 0, NULL) == -1)
    return -1;
      
  *tgt = mutt_new_body ();
  b = *tgt;

  memcpy (b, src, sizeof (BODY));
  b->parts = NULL;
  b->next  = NULL;

  b->filename = safe_strdup (tmp);
  b->use_disp = use_disp;
  b->unlink = 1;

  if (mutt_is_text_part (b))
    b->noconv = 1;

  b->xtype = safe_strdup (b->xtype);
  b->subtype = safe_strdup (b->subtype);
  b->form_name = safe_strdup (b->form_name);
  b->filename = safe_strdup (b->filename);
  b->d_filename = safe_strdup (b->d_filename);
  b->description = safe_strdup (b->description);

  

  if (b->hdr) b->hdr = NULL;
  
  
  for (par = b->parameter, ppar = &b->parameter; par; ppar = &(*ppar)->next, par = par->next)
  {
    *ppar = mutt_new_parameter ();
    (*ppar)->attribute = safe_strdup (par->attribute);
    (*ppar)->value = safe_strdup (par->value);
  }

  mutt_stamp_attachment (b);
  
  return 0;
}