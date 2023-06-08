# LXEB

- Revision 1 is incorrect for n >= 2
- Revision 2 seems correct!
- Revision 3 is the same as revision 2, but instead of working symbolically with k, we work with coefficient arrays representing the coefficients in front of certain degrees of k. This dramatically speeds the code up. It write the results to the CSV file.


The WithIO folder builds off of revision 3.
- recursionIO.nb: Everytime you run the computeG function, it appends new computed values to the computedG.csv file. Everytime you restart the notebook, it loads the precomputed values from the computedG.csv file.
- playingAround.nb: Here we just load all of the data from computedG.csv so we can more easily play around with it.

The Julia folder is the same as the WithIO folder except that it is written in Julia instead of Mathematica. It seems to be considerably faster, even though I don't have Julia locally installed and so was doing it on cocalc.com. We can easily get to large values of n with Julia, and even larger values with a Julia on a cluster.

The cpp-code folder contains some code to check some of Adam's older formulas. It also contains code to generate a bunch of random Gaussian matrices and estimate the average and standard deviation of the fourth moment.

