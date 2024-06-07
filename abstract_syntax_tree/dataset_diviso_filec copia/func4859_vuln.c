stringprep_strerror (Stringprep_rc rc)
{
  const char *p;

  bindtextdomain (PACKAGE, LOCALEDIR);

  switch (rc)
    {
    case STRINGPREP_OK:
      p = _("STR");
      break;

    case STRINGPREP_CONTAINS_UNASSIGNED:
      p = _("STR");
      break;

    case STRINGPREP_CONTAINS_PROHIBITED:
      p = _("STR");
      break;

    case STRINGPREP_BIDI_BOTH_L_AND_RAL:
      p = _("STR");
      break;

    case STRINGPREP_BIDI_LEADTRAIL_NOT_RAL:
      p = _("STR");
      break;

    case STRINGPREP_BIDI_CONTAINS_PROHIBITED:
      p = _("STR");
      break;

    case STRINGPREP_TOO_SMALL_BUFFER:
      p = _("STR");
      break;

    case STRINGPREP_PROFILE_ERROR:
      p = _("STR");
      break;

    case STRINGPREP_FLAG_ERROR:
      p = _("STR");
      break;

    case STRINGPREP_UNKNOWN_PROFILE:
      p = _("STR");
      break;

    case STRINGPREP_NFKC_FAILED:
      p = _("STR");
      break;

    case STRINGPREP_MALLOC_ERROR:
      p = _("STR");
      break;

    default:
      p = _("STR");
      break;
    }

  return p;
}