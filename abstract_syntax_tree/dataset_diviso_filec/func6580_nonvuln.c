  Nef_polyhedron_2(const Plane_map& H, bool clone=true) : Base(Nef_rep())
  
  { if (clone) {
      Decorator D(pm()); 
      D.clone(H);        
    }
  }