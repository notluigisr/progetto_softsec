Opal::Call::OnHold (OpalConnection & , 
                    bool , 
                    bool on_hold)
{
  if (on_hold)
    Ekiga::Runtime::run_in_main (boost::bind (&Opal::Call::emit_held_in_main, this));
  else
    Ekiga::Runtime::run_in_main (boost::bind (&Opal::Call::emit_retrieved_in_main, this));
}