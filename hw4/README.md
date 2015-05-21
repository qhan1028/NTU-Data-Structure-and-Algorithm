dsa14hw4
========

Data Structure and Algorithm Homework 4

The first argument of both `tree_predictor.cpp` and `forest_predictor.cpp`
is the test (prediction) data in the format same as training data, and the
output is the accuray of the predictor on the test data.

For example,

    ./tree_predictor heart.test

Usage of the `Makefile.ta`:

1. `make run_tree FNAME=heart.train EPSILON=0.1`: 

   run the decision tree on data `heart.train` with epsilon=0.1.

2. `make run_forest FNAME=heart.train T=30`:

   run the random forest with 30 trees on data `heart.train`.

3. `make predict_tree PNAME=heart.test`:

   make prediction by the decision tree model on data `heart.test`.

4. `make predict_forest PNAME=heart.test`:

   make prediction by random forest model on data `heart.test`.

You can play around with different `FNAME`, `PNAME` and `T`.

We provide two sample data, heart and a1a. The heart data set describes diagnosing of cardiac Single Proton Emission Computed Tomography (SPECT) images. The label means two catogories of patients : normal and abnormal. The features are

1. F1R: continuous (count in ROI (region of interest) 1 in rest)

2. F1S: continuous (count in ROI 1 in stress)

3. F2R: continuous (count in ROI 2 in rest)

4. F2S: continuous (count in ROI 2 in stress)

5. F3R: continuous (count in ROI 3 in rest)

6. F3S: continuous (count in ROI 3 in stress)

7. F4R: continuous (count in ROI 4 in rest)

8. F4S: continuous (count in ROI 4 in stress)

...

The a1a data set describes whether each example (an adult) is of income exceeding $50K/yr.

Both data sets are from 

http://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/binary.html

Please feel free to play your trees with more data sets there.
