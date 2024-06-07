Opal::Call::get_duration () const
{
  std::stringstream duration;
  
  if (start_time.IsValid () && IsEstablished ()) {

    PTimeInterval t = PTime () - start_time;

    duration << setfill ('0') << setw (2) << t.GetHours () << "STR";
    duration << setfill ('0') << setw (2) << (t.GetMinutes () % 60) << "STR";
    duration << setfill ('0') << setw (2) << (t.GetSeconds () % 60);
  }

  return duration.str ();
}