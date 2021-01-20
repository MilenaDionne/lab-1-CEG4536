#include <iostream>
#include <omp.h>
#include <mutex>

using namespace std; 
#define NUM_THREADS 16 
std::mutex mu; 
//test

//test branch
/*
Function: fibonacci_parallel
Description: Recursive fibonacci serie in parallel function
*/
int fibonacci_parallel(int n) { 
	if (n < 2) {
		return 1;
	}
	return fibonacci_parallel(n - 2) + fibonacci_parallel(n - 1);
}

/*
Function: fibonacci_serial
Description: Recursive fibonacci serie in serial function
*/
int fibonacci_serial(int n) {
	if (n < 2) {
		return 1;
	}
	return fibonacci_parallel(n - 2) + fibonacci_parallel(n - 1);
}

/*
Function: main
Description: effectue série de fibonacci en série et en parallèle pour récursive et non-récursive
*/

int main() {
	int sum = 0;
	int n1 = 0, n2 = 1, n3 = 0, i = 0, number;
	cout << "Enter the number of elements to the fibonacci serie (time start after number entered): ";
	cin >> number;
	
	cout << "\n********************Non-Recursive Fibonacci serial***********************" << endl;

	double start_nonr = omp_get_wtime();
	for (int i = 2; i <= number; i++) {
		n3 = n1 + n2;
		n1 = n2;
		n2 = n3;
	}
	sum = n3;
	double end_nonr = omp_get_wtime();

	cout << "\nsum = " << sum << endl;
	cout << "temps d'execution: " << (end_nonr - start_nonr) << endl << endl;

	cout << "\n********************Non-Recursive Fibonacci parallel***********************" << endl;
	omp_set_num_threads(NUM_THREADS);
	double start_parallel_nonr = omp_get_wtime();
 
#pragma omp parallel for private (n1,n2,n3) 	//private creates a new local copy of n1,n2 and n3 for each thread
	for (int i = 2; i <= number; i++) {
		n3 = n1 + n2;
		n1 = n2;
		n2 = n3;
	}
		
	sum = n3;
	double end_parallel_nonr = omp_get_wtime();

	cout << "\nsum = " << sum << endl;
	cout << "temps d'execution: " << (end_parallel_nonr - start_parallel_nonr) << endl << endl;
	cout << "\nParallel fibonacci serie in non-recursive is " << (end_nonr - start_nonr) - (end_parallel_nonr - start_parallel_nonr) << " seconds faster than serial fibonacci recursive" << endl;
	
	cout << "\n********************Recursive Finbonacci serial***********************" << endl;

	double start = omp_get_wtime();
	for (int i = 2; i <= number; i++) {
		sum = fibonacci_serial(i - 1);
	}
	double end = omp_get_wtime();

	cout << "\nsum = " << sum << endl;
	cout << "temps d'execution: " << (end - start) << endl << endl;


	n1 = 0, n2 = 1, n3 = 0, i = 0, number;
	cout << "********************Recursive Finbonnacci parallel***********************" << endl;
	omp_set_num_threads(NUM_THREADS);
	double start_parallel = omp_get_wtime();

#pragma omp parallel for 
	for (int i = 2; i <= number; i++) {
		sum = fibonacci_parallel(i - 1);
	}

	double end_parallel = omp_get_wtime();

	cout << "\nsum = " << sum << endl;
	cout << "temps d'execution: " << end_parallel - start_parallel << endl;
	cout << "\nParallel fibonacci serie in recursive is " << (end - start) - (end_parallel - start_parallel) << " seconds faster than serial fibonacci recursive" << endl;

	return 0; 
	
}
