### opa2.pdf
This is a preprint of an article published in Scientific Reports (Haruna, T., Gunji, Y.-P., 2020. Analysis and synthesis of a growing network model generating dense scale-free networks via category theory. Scientific Reports 10, 22351.
). The final authenticated version is available online at:
https://doi.org/10.1038/s41598-020-79318-7".

The followings are the source codes and data used in the paper.

We use GCC (https://gcc.gnu.org/) and GSL (https://www.gnu.org/software/gsl/). 

### opa2.c
The code for simulating the new model and generating "id-deg-knn-cc_tX_trialY.txt" (X: sampled time step, Y: trial number) 

The codes used in our numerical experiment and a sample of the generated files are contained in data_opa2_delta_Z (Z: value of delta).

### opa1adj.c
The code for simulating the previous model with the adjunction rule and generating "id-deg-knn-cc_tX_trialY.txt"

The codes used in our numerical experiment and a sample of the generated files are contained in data_opa1adj_delta_sqrt3-2.
  
### id-deg-knn-cc_tX_trialY.txt
- 1st column: Node ID
- 2nd column: Degree of the node specified by the ID at the 1st column
- 3rd column: The average degree of the neighboring nodes of the node
- 4th column: The local clustering coefficient of the node

### figdata.c
The code for generating "degav-ccav.txt" and "degdist-knn-ck_tX.txt" from "id-deg-knn-cc_tX_trialY.txt".

The codes used in our numerical experiment and the generated files are contained in data_opa2_delta_Z and data_opa1adj_delta_Z.
 
### degav-ccav.txt
- 1st column: Time step
- 2nd column: The average of the average degree over the all trials.
- 3rd column: The average of the average local clustering coefficient over the all trials.
 
### degdist-knn-ck_tX.txt
- 1st column: Degree k
- 2nd column: The average of the degree distributions over the all trials
- 3rd column: The average of k_{nn}(k) over the all trials in which there exists at least one node of degree k
- 4th column: The average of C(k) over the all trials in which there exists at least one node of degree k
- 5th column: The number of trials in which there exists at least one node of degree k
 
### Figure 2
- (1st column) vs (2nd column) in degdist-knn-ck_t65536.txt for opa1adj with delta=sqrt(1.5)
 
### Figure 3
- (1st column) vs (2nd column) in degdist-knn-ck_tX.txt for opa2
 
### Figure 4
- (1st column) vs 0.5(1st column)(2nd column) in degav-ccav.txt for opa2

The data for t=512 are discarded.
 
### Figure 5
- (1st column) vs (3nd column) in degdist-knn-ck_tX.txt and  for opa2
- (2st column) vs (3nd column) in id-deg-knn-cc_tX_trial99.txt
 
### Figure 6
- (1st column) vs (4nd column) in degdist-knn-ck_tX.txt for opa2
- (2st column) vs (4nd column) in id-deg-knn-cc_tX_trial99.txt
  
