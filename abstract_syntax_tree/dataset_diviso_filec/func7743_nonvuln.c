void WebContents::InitWithExtensionView(v8::Isolate* isolate,
                                        content::WebContents* web_contents,
                                        extensions::mojom::ViewType view_type) {
  
  type_ = GetTypeFromViewType(view_type);
  if (type_ == Type::kRemote)
    return;
  if (type_ == Type::kBackgroundPage)
    
    
    
    
    Pin(isolate);

  
  Observe(web_contents);
  InitWithWebContents(std::unique_ptr<content::WebContents>(web_contents),
                      GetBrowserContext(), IsGuest());
  inspectable_web_contents_->GetView()->SetDelegate(this);
}