
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *yyscanner, RE_LEX_ENVIRONMENT *lex_env)
{
  YYUSE (yyvaluep);
  YYUSE (yyscanner);
  YYUSE (lex_env);
  if (!yymsg)
    yymsg = "STR";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 6: 
#line 96 "STR" 
      { yr_free(((*yyvaluep).class_vector)); }
#line 1045 "STR" 
        break;

    case 26: 
#line 97 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1051 "STR" 
        break;

    case 27: 
#line 98 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1057 "STR" 
        break;

    case 28: 
#line 99 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1063 "STR" 
        break;

    case 29: 
#line 100 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1069 "STR" 
        break;


      default:
        break;
    }