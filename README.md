# LXEB

*TO DO*: add description with link to paper.


#### Recursion folder

The `Recursion` folder contains the subfolders `MathematicaRecursion` and `JuliaRecursion`. `MathematicaRecursion` contains Mathematica files (these can also be opened and run with WolframScript, which is a free alternative to Mathematica). The `recursion.nb` file performs the recursion to exactly compute the values of g(n, a_{12}, a_{13}, a_{23}) (with g(n, 0, 0, 0) being a special case). It loads the precomputed values from `computedG.csv`, and as it computes more values, it appends the resulting values to `computedG.csv`.

The `JuliaRecursion` folder performs the same recursion as is performed in the `MathematicaRecursion` folder. However, it is written in Julia and so is _much much_ faster. The code is however mostly uncommented. But it is a direct translation of the Mathematica code, and the Mathematica code _is_ heavily commented. Hence, if you want to understand the code, we recommend reading the Mathematica code; if you want to run the code, we recommend running the Julia code.

We emphasize that in both the Mathematica and Julia code, polynomials in k (e.g. a + b k + c k^2) are represented as arrays ({a, b, c}). Multiplying and adding polynomials is then done via functions on the array representations. Using this representation _dramatically_ speeds up the code in comparison to e.g. working with k symbolically in Mathematica.


#### Analysis folder

*TO DO*: describe this section better.

In the `sanityChecks.nb` file, we load the computed values of g from `Recursion/JuliaRecursion/computedG.csv` and perform some of the sanity checks described in the paper on it.

In the `plot-fits.nb` file, we load the computed values of g from `Recursion/JuliaRecursion/computedG.csv` and make some plots.


#### NumericalApprox folder

The `NumericalApprox` folder contains the code to (a) generate numerical estimates of the fourth moment of the Hafnian (second moment in GBS probabilities) (`numerical_approx_fourth_moment.py`), and to (b) plot those estimates on top of the analytical results we find in the `Recursion` folder.


## IMPORTANT!

I ran the Julia code `Recursion/JuliaRecursion/recursion.jl` up to n=40. Unfortunately, `Recursion/JuliaRecursion/computedG.csv` is very large now (about 198 MB), and `git push` is freezing so I can't upload the full file to GitHub. 

The current `Recursion/JuliaRecursion/computedG.csv` file on GitHub goes only to n=9. The file that contains up to n=40 is on [Google Drive](https://drive.google.com/drive/folders/1sCdtR_jjV6ohsK2928Ki3WuEgbaKxJkt?usp=share_link). 

The easiest way to play around with the expressions is to clone the repo, download the `computedG.csv` file from Drive and replace the `Recursion/JuliaRecursion/computedG.csv` file with it, then run `Analysis/sanityChecks.nb`.


