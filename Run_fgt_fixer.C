
void Run_fgt_fixer(){ 
  gROOT->LoadMacro("fgt_fixer.C");
  fgt_fixer t;
  //t.Show(16);
  t.Loop();
}

