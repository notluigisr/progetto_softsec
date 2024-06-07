print_command_failed (const unsigned char *msg)
{
  const char *t;
  char buffer[100];
  int ec;

  if (!debug_level)
    return;

  ec = CCID_ERROR_CODE (msg);
  switch (ec)
    {
    case 0x00: t = "STR"; break;

    case 0xE0: t = "STR"; break;
    case 0xEF: t = "STR"; break;
    case 0xF0: t = "STR"; break;

    case 0xF2: t = "STR"; break;
    case 0xF3: t = "STR"; break;
    case 0xF4: t = "STR"; break;
    case 0xF5: t = "STR"; break;
    case 0xF6: t = "STR"; break;
    case 0xF7: t = "STR"; break;
    case 0xF8: t = "STR"; break;

    case 0xFB: t = "STR"; break;
    case 0xFC: t = "STR"; break;
    case 0xFD: t = "STR"; break;
    case 0xFE: t = "STR"; break;
    case 0xFF: t = "STR"; break;

    default:
      if (ec > 0 && ec < 128)
        sprintf (buffer, "STR", ec);
      else
        sprintf (buffer, "STR", ec);
      t = buffer;
      break;
    }
  DEBUGOUT_1 ("STR", t);
}