    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
                     CImgDisplay& disp6, CImgDisplay& disp7, CImgDisplay& disp8, CImgDisplay& disp9,
                     CImgDisplay& disp10) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
        disp6._is_event = disp7._is_event = disp8._is_event = disp9._is_event = disp10._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
              !disp6._is_closed || !disp7._is_closed || !disp8._is_closed || !disp9._is_closed || !disp10._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
             !disp6._is_event && !disp7._is_event && !disp8._is_event && !disp9._is_event && !disp10._is_event)
        wait_all();
    }