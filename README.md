# LXEB

- Revision 1 is incorrect for n >= 2
- Revision 2 seems correct!
- Revision 3 is the same as revision 2, but instead of working symbolically with k, we work with coefficient arrays representing the coefficients in front of certain degrees of k. This dramatically speeds the code up. It write the results to the CSV file.


The WithIO folder builds off of revision 3.
- recursionIO.nb: Everytime you run the computeG function, it appends new computed values to the computedG.csv file. Everytime you restart the notebook, it loads the precomputed values from the computedG.csv file.
- playingAround.nb: Here we just load all of the data from computedG.csv so we can more easily play around with it.
