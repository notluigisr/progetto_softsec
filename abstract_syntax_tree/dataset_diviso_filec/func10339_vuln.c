addtok (token t)
{
  if (MB_CUR_MAX > 1 && t == MBCSET)
    {
      bool need_or = false;
      struct mb_char_classes *work_mbc = &dfa->mbcsets[dfa->nmbcsets - 1];

      
      if (!work_mbc->invert)
        {
          int i;
          for (i = 0; i < work_mbc->nchars; i++)
            {
              addtok_wc (work_mbc->chars[i]);
              if (need_or)
                addtok (OR);
              need_or = true;
            }
          work_mbc->nchars = 0;
        }

      
      if (work_mbc->invert
          || (!using_utf8() && work_mbc->cset != -1)
          || work_mbc->nchars != 0
          || work_mbc->nch_classes != 0
          || work_mbc->nranges != 0
          || work_mbc->nequivs != 0
          || work_mbc->ncoll_elems != 0)
        {
          addtok_mb (MBCSET, ((dfa->nmbcsets - 1) << 2) + 3);
          if (need_or)
            addtok (OR);
        }
      else
        {
          
          if (work_mbc->cset != -1)
            {
              assert (using_utf8 ());
              addtok (CSET + work_mbc->cset);
              if (need_or)
                addtok (OR);
            }
        }
    }
  else
    {
      addtok_mb (t, 3);
    }
}