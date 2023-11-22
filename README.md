# Homework 2

## Task 1

Description of code 

The two files task1.1 and task1.2 are respectivly the sequential and the parallel code. The function matMul() is the one doing the operation. When you run the function the calculation time is printed. This is the respective times of the parallel or serial section. 

In the main function two matrices are generated, then multiplied using the matMul() function. After the code is executed the calculation time is printed. Edit the variable "dimention" in main to run the code with a different matrix size. 

The task1.2.pbs file is for running the code on the cluster. In this file it is spesified that the code shoude be run two times by 1, 2, 4, 8, 16, 32 and 64 threads. The result is then printed 14 times in respectivly order. 

How to run the code 

I ran task1.1.c on my computer in the terminal using the following steps:
- gcc -o task1.1 task1.1.c
- ./task1.1<br>
NB my compiler is Apple clang version 14.0.3, and I have an Apple silicon architecure. 

In order to run task1.2.pbs the working directory writen in the file must be editied. This is line 35. 
I ran task1.2.c on the cluster using the following steps: 
- module mpich -3.2 
- qsub task1.2.pbs<br>
a task1.2.o file is now created. At the bottom of this file the results of the calcualtion could be found. 


## Task 2

Description of code 

The two files task2.1 and task2.2 are respectivly the sequential and the parallel code. Inside both files tou have the matT() function and the matBlockT() function. These are the functions doing the calculations. When you run the one of the functions the calculation time is printed. This is the respective times of the parallel or serial section. 

In the main function one matrix is generated. You can then choose which function you want to use by uncommenting one of the lines marked with: "UNCOMMENT THIS LINE TO USE THE **** FUNCTION". Edit the variable "dimention" and "blocksize" in main to run the code with a different matrix size and with different block divition. 

The task2.2.pbs file is for running the code on the cluster. In this file it is spesified that the code shoude be run by 1, 16 and 64 threads. The result is then printed 3 times in respectivly order. 

How to run the code 

I ran task2.1 on my computer in the terminal using the following steps:
- gcc -o task2.1 task2.1.c
- ./task2.1<br>
NB my compiler is Apple clang version 14.0.3, and I have an Apple silicon architecure. 

In order to run task1.2.pbs the working directory writen in the file must be editied. This is line 35.
I ran task2.2 on the cluster using the following steps: 
- module mpich -3.2 
- qsub task2.2.pbs<br>
a task2.2.o file is now created. At the bottom of this file the results of the calculation could be found. 

