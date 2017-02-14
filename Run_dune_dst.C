
void Run_dune_dst(int mySeed=0){ 
  gROOT->LoadMacro("dune_dst.C");
  dune_dst t;
  //t.Show(16);
  t.Loop(mySeed);
}

