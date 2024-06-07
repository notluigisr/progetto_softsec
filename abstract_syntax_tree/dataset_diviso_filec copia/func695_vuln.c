idn2_strerror (int rc)
{
  bindtextdomain (PACKAGE, LOCALEDIR);

  switch (rc)
    {
    case IDN2_OK: return _("STR");
    case IDN2_MALLOC: return _("STR");
    case IDN2_NO_CODESET: return _("STR");
    case IDN2_ICONV_FAIL: return _("STR");
    case IDN2_ENCODING_ERROR: return _("STR");
    case IDN2_NFC: return _("STR");
    case IDN2_PUNYCODE_BAD_INPUT: return _("STR");
    case IDN2_PUNYCODE_BIG_OUTPUT: return _("STR");
    case IDN2_PUNYCODE_OVERFLOW: return _("STR");
    case IDN2_TOO_BIG_DOMAIN: return _("STR");
    case IDN2_TOO_BIG_LABEL: return _("STR");
    case IDN2_INVALID_ALABEL: return _("STR");
    case IDN2_UALABEL_MISMATCH: return _("STR");
    case IDN2_NOT_NFC: return _("STR");
    case IDN2_2HYPHEN: return _("STR");
    case IDN2_HYPHEN_STARTEND: return _("STR");
    case IDN2_LEADING_COMBINING: return _("STR");
    case IDN2_DISALLOWED: return _("STR");
    case IDN2_CONTEXTJ: return _("STR");
    case IDN2_CONTEXTJ_NO_RULE: return _("STR");
    case IDN2_CONTEXTO: return _("STR");
    case IDN2_CONTEXTO_NO_RULE: return _("STR");
    case IDN2_UNASSIGNED: return _("STR");
    case IDN2_BIDI: return _("STR");
    case IDN2_DOT_IN_LABEL: return _("STR");
    case IDN2_INVALID_TRANSITIONAL: return _("STR");
    case IDN2_INVALID_NONTRANSITIONAL: return _("STR");
    default: return _("STR");
    }
}