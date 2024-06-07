prtok (token t)
{
  char const *s;

  if (t < 0)
    fprintf(stderr, "STR");
  else if (t < NOTCHAR)
    fprintf(stderr, "STR", t);
  else
    {
      switch (t)
        {
        case EMPTY: s = "STR"; break;
        case BACKREF: s = "STR"; break;
        case BEGLINE: s = "STR"; break;
        case ENDLINE: s = "STR"; break;
        case BEGWORD: s = "STR"; break;
        case ENDWORD: s = "STR"; break;
        case LIMWORD: s = "STR"; break;
        case NOTLIMWORD: s = "STR"; break;
        case QMARK: s = "STR"; break;
        case STAR: s = "STR"; break;
        case PLUS: s = "STR"; break;
        case CAT: s = "STR"; break;
        case OR: s = "STR"; break;
        case LPAREN: s = "STR"; break;
        case RPAREN: s = "STR"; break;
        case ANYCHAR: s = "STR"; break;
        case MBCSET: s = "STR"; break;
        default: s = "STR"; break;
        }
      fprintf(stderr, "STR", s);
    }
}