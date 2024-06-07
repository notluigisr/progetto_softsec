void ElectronBrowserClient::
    RegisterAssociatedInterfaceBindersForRenderFrameHost(
        content::RenderFrameHost&
            render_frame_host,  
        blink::AssociatedInterfaceRegistry&
            associated_registry) {  
  associated_registry.AddInterface(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<electron::mojom::ElectronBrowser>
             receiver) {
        ElectronBrowserHandlerImpl::Create(render_frame_host,
                                           std::move(receiver));
      },
      &render_frame_host));
  associated_registry.AddInterface(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<mojom::ElectronAutofillDriver>
             receiver) {
        AutofillDriverFactory::BindAutofillDriver(std::move(receiver),
                                                  render_frame_host);
      },
      &render_frame_host));
#if BUILDFLAG(ENABLE_PRINTING)
  associated_registry.AddInterface(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<printing::mojom::PrintManagerHost>
             receiver) {
        PrintViewManagerElectron::BindPrintManagerHost(std::move(receiver),
                                                       render_frame_host);
      },
      &render_frame_host));
#endif
#if BUILDFLAG(ENABLE_EXTENSIONS)
  associated_registry.AddInterface(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<extensions::mojom::LocalFrameHost>
             receiver) {
        extensions::ExtensionWebContentsObserver::BindLocalFrameHost(
            std::move(receiver), render_frame_host);
      },
      &render_frame_host));
#endif
#if BUILDFLAG(ENABLE_PDF_VIEWER)
  associated_registry.AddInterface(base::BindRepeating(
      [](content::RenderFrameHost* render_frame_host,
         mojo::PendingAssociatedReceiver<pdf::mojom::PdfService> receiver) {
        pdf::PDFWebContentsHelper::BindPdfService(std::move(receiver),
                                                  render_frame_host);
      },
      &render_frame_host));
#endif
}