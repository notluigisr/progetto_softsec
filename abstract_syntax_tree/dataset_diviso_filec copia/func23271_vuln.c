idna_strerror (Idna_rc rc)
{
  const char *p;

  bindtextdomain (PACKAGE, LOCALEDIR);

  switch (rc)
    {
    case IDNA_SUCCESS:
      p = _("STR");
      break;

    case IDNA_STRINGPREP_ERROR:
      p = _("STR");
      break;

    case IDNA_PUNYCODE_ERROR:
      p = _("STR");
      break;

    case IDNA_CONTAINS_NON_LDH:
      p = _("STR");
      break;

    case IDNA_CONTAINS_MINUS:
      p = _("STR");
      break;

    case IDNA_INVALID_LENGTH:
      p = _("STR");
      break;

    case IDNA_NO_ACE_PREFIX:
      p = _("STR");
      break;

    case IDNA_ROUNDTRIP_VERIFY_ERROR:
      p = _("STR");
      break;

    case IDNA_CONTAINS_ACE_PREFIX:
      p = _("STR");
      break;

    case IDNA_ICONV_ERROR:
      p = _("STR");
      break;

    case IDNA_MALLOC_ERROR:
      p = _("STR");
      break;

    case IDNA_DLOPEN_ERROR:
      p = _("STR");
      break;

    default:
      p = _("STR");
      break;
    }

  return p;
}