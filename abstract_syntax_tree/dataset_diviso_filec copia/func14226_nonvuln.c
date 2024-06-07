    static int Raw(llhttp_t* p, Args ... args) {
      Parser* parser = ContainerOf(&Parser::parser_, p);
      int rv = (parser->*Member)(std::forward<Args>(args)...);
      if (rv == 0) {
        rv = parser->MaybePause();
      }
      return rv;
    }