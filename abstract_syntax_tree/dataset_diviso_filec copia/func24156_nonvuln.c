linear_gradient_apply_fallback (gpointer data, gpointer fallback_data)
{
    RsvgNode *node;
    RsvgLinearGradient *grad;
    RsvgNode *fallback_node;

    node = data;
    g_assert (RSVG_NODE_TYPE (node) == RSVG_NODE_TYPE_LINEAR_GRADIENT);
    grad = (RsvgLinearGradient *) node;

    fallback_node = fallback_data;

    if (RSVG_NODE_TYPE (fallback_node) == RSVG_NODE_TYPE_LINEAR_GRADIENT) {
        RsvgLinearGradient *fallback = (RsvgLinearGradient *) fallback_node;

        if (!grad->hasx1 && fallback->hasx1) {
            grad->hasx1 = TRUE;
            grad->x1 = fallback->x1;
        }
        if (!grad->hasy1 && fallback->hasy1) {
            grad->hasy1 = TRUE;
            grad->y1 = fallback->y1;
        }
        if (!grad->hasx2 && fallback->hasx2) {
            grad->hasx2 = TRUE;
            grad->x2 = fallback->x2;
        }
        if (!grad->hasy2 && fallback->hasy2) {
            grad->hasy2 = TRUE;
            grad->y2 = fallback->y2;
        }
        if (!grad->hastransform && fallback->hastransform) {
            grad->hastransform = TRUE;
            grad->affine = fallback->affine;
        }
        if (!grad->hasspread && fallback->hasspread) {
            grad->hasspread = TRUE;
            grad->spread = fallback->spread;
        }
        if (!grad->hasbbox && fallback->hasbbox) {
            grad->hasbbox = TRUE;
            grad->obj_bbox = fallback->obj_bbox;
        }
        if (!hasstop (grad->super.children) && hasstop (fallback->super.children)) {
            grad->super.children = fallback->super.children;
        }
    } else if (RSVG_NODE_TYPE (fallback_node) == RSVG_NODE_TYPE_RADIAL_GRADIENT) {
        RsvgRadialGradient *fallback = (RsvgRadialGradient *) fallback_node;

        if (!grad->hastransform && fallback->hastransform) {
            grad->hastransform = TRUE;
            grad->affine = fallback->affine;
        }
        if (!grad->hasspread && fallback->hasspread) {
            grad->hasspread = TRUE;
            grad->spread = fallback->spread;
        }
        if (!grad->hasbbox && fallback->hasbbox) {
            grad->hasbbox = TRUE;
            grad->obj_bbox = fallback->obj_bbox;
        }
        if (!hasstop (grad->super.children) && hasstop (fallback->super.children)) {
            grad->super.children = fallback->super.children;
        }
    }
}