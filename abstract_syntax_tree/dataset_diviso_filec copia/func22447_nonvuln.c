bool SpellCheckWord(content::RenderFrame* render_frame,
                    const std::string& word,
                    std::vector<std::u16string>* optional_suggestions) {
  size_t start;
  size_t length;

  RendererClientBase* client = RendererClientBase::Get();

  std::u16string w = base::UTF8ToUTF16(word);
  int id = render_frame->GetRoutingID();
  return client->GetSpellCheck()->SpellCheckWord(
      w.c_str(), 0, word.size(), id, &start, &length, optional_suggestions);
}