string InferenceContext::DebugString() const {
  return strings::StrCat("STR", attrs_.SummarizeNode());
}