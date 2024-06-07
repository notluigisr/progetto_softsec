static void dumpCallArguments(
    llvh::raw_ostream &OS,
    Runtime *runtime,
    StackFramePtr calleeFrame) {
  OS << "STR";
  OS << "STR" << DumpHermesValue(calleeFrame.getThisArgRef())
     << "STR";
  for (unsigned i = 0; i < calleeFrame.getArgCount(); ++i) {
    OS << "STR" << DumpHermesValue(calleeFrame.getArgRef(i))
       << "STR";
  }
}