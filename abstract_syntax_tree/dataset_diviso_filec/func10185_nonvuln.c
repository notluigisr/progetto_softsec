  explicit ReplaceMulWithBroadcastByTile(
      const GraphOptimizerContext& ctx,
      const ArithmeticOptimizerContext& ctx_ext)
      : ArithmeticOptimizerStage("STR", ctx,
                                 ctx_ext) {}