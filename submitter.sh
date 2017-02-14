#!/bin/bash
for i in `seq 1 2000`;
do
    echo "#!/usr/bin/env bash  " >> "job_grid_${i}.sh"
    echo "source /grid/fermiapp/products/dune/setup_dune.sh" >> "job_grid_${i}.sh"
    echo "setup root v5_34_32 -q e9:nu:prof" >> "job_grid_${i}.sh"
    echo "setup ifdhc" >> "job_grid_${i}.sh"

    echo "export USRDIR=/dune/app/users/lorena/DetSystRWtool " >>  "job_grid_${i}.sh"
    echo "export OUTDIR=/pnfs/dune/scratch/users/lorena/DetSyst " >> "job_grid_${i}.sh"
    echo "ifdh cp /dune/app/users/lorena/DetSystRWtool/fgt_events_nu.root ./fgt_events_nu.root " >> "job_grid_${i}.sh"
    echo "ifdh cp /dune/app/users/lorena/DetSystRWtool/fgt_events_nubar.root ./fgt_events_nubar.root " >> "job_grid_${i}.sh"

    echo "ifdh cp /dune/app/users/lorena/DetSystRWtool/dune_dst.C ./dune_dst.C" >> "job_grid_${i}.sh"
    echo "ifdh cp /dune/app/users/lorena/DetSystRWtool/dune_dst.h ./dune_dst.h" >> "job_grid_${i}.sh"
    echo "ifdh cp /dune/app/users/lorena/DetSystRWtool/DetSystRWtool.cxx ./DetSystRWtool.cxx " >> "job_grid_${i}.sh"
    echo "ifdh cp /dune/app/users/lorena/DetSystRWtool/DetSystRWtool.h ./DetSystRWtool.h " >> "job_grid_${i}.sh"
    echo "ifdh cp /dune/app/users/lorena/DetSystRWtool/Run_dune_dst.C ./Run_dune_dst.C">> "job_grid_${i}.sh"

    seed=$((i*1000))
    echo "root -l -b -q 'Run_dune_dst.C(${seed})' " >> "job_grid_${i}.sh"
    echo "ifdh cp det_eff_fgt.root \${OUTDIR}/det_eff_fgt_${i}.root" >> "job_grid_${i}.sh"

    jobsub_submit -N 1 --OS=SL6 --group dune --role=Analysis --expected-lifetime=24h file:///dune/app/users/lorena/DetSystRWtool/jobs/job_grid_${i}.sh

done