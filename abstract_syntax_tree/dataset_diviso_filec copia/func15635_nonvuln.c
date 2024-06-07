size_t miller_rabin_test_iterations(size_t bits, size_t level)
   {
   struct mapping { size_t bits; size_t verify_iter; size_t check_iter; };

   static const mapping tests[] = {
      {   50, 55, 25 },
      {  100, 38, 22 },
      {  160, 32, 18 },
      {  163, 31, 17 },
      {  168, 30, 16 },
      {  177, 29, 16 },
      {  181, 28, 15 },
      {  185, 27, 15 },
      {  190, 26, 15 },
      {  195, 25, 14 },
      {  201, 24, 14 },
      {  208, 23, 14 },
      {  215, 22, 13 },
      {  222, 21, 13 },
      {  231, 20, 13 },
      {  241, 19, 12 },
      {  252, 18, 12 },
      {  264, 17, 12 },
      {  278, 16, 11 },
      {  294, 15, 10 },
      {  313, 14,  9 },
      {  334, 13,  8 },
      {  360, 12,  8 },
      {  392, 11,  7 },
      {  430, 10,  7 },
      {  479,  9,  6 },
      {  542,  8,  6 },
      {  626,  7,  5 },
      {  746,  6,  4 },
      {  926,  5,  3 },
      { 1232,  4,  2 },
      { 1853,  3,  2 },
      {    0,  0,  0 }
   };

   for(size_t i = 0; tests[i].bits; ++i)
      {
      if(bits <= tests[i].bits)
         {
         if(level >= 2)
            return tests[i].verify_iter;
         else if(level == 1)
            return tests[i].check_iter;
         else if(level == 0)
            return std::max<size_t>(tests[i].check_iter / 4, 1);
         }
      }

   return level > 0 ? 2 : 1; 
   }