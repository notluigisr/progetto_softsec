gs_window_clear (GSWindow *window)
{
        g_return_if_fail (GS_IS_WINDOW (window));

        clear_widget (GTK_WIDGET (window));
        clear_widget (window->priv->drawing_area);
}