--- Files ---

- DetSystRWtool.cxx and DetSystRWtool.h: Classes written by Dan to throw a random number for efficiencies and resolutions and calculate new Ereco, yreco and sample. My updates: added the random seed in the constructor, and updated the definition of samples.

- dune_dst.C: root macro looping over events and storing the vector of number of events in each bin after a tweak of efficiencies and resolutions. Hopefully the comments are self explanatory. I have added my own comments to the ones by Dan

- setup.sh: for root etc, update if you want a different version of the products there

- fgt_fixer.C: this is to skim Brian's files and store only the branches we need, making the code faster in this way. It also contains specific function from Chris to calculate the weight used in VALOR to select if events are used depending on the target of the interaction, other detecgors should ignore/remove this part

- Run_fgt_fixer.C: macro to run the above

- submitter.sh: bash script to submit jobs to Fermigrid - change seed calculation as you wish, change file location path

- make_cov_matrix.C: macro to compute the covariance matrix with a vector containing all tweaks

--- Instructions ---

* -1 - source setup.sh
* 0 - edit fgt_fixer.h to give the path and name of your input files (Brian's files), run Run_fgt_fixer.C to skim them. 
* 1 - Edit dune_dst.C to select the number of tweaks per job you want to use, and dune_dst.h to give the path and name of the files to use. Submit jobs with submitter.sh to get the number of throws you want 
* 2 - If you have more than one job submitted, you will need to combine the output from all your jobs into a single vector prior to run make_cov_matrix_mean.C
* 3 - Finally edit and run make_cov_matrix to compute the covariance matrix (version using the mean value for each bin, if you want to use the nominal you will need an extra step to calculate the nominal number of events per bin by running once dune_dst.C without tweaks)

Note: a single loop over the 1.8M events for the FGT takes ~2 hours
Note: in case of many tweaks, ROOT might give problems and you might need to run make_cov_matrix.C several times on a fraction of the tweaks and then combine the output to compute the final covariance matrix 
