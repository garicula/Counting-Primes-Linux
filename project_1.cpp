//Project 1 CPSC 330
//Garrick, Dylan, and TJ
//This is a program where the user inputs the start number, stop number, and
//number of processes, and then the program returns the amount of prime
//numbers.

#define _REENTRANT
#include <iostream>
#include <cmath>
#include <pthread.h>
#include <bits/stdc++.h>
using namespace std;

int sum, beginning, ending, nthreads;	//Global variables
pthread_mutex_t my_lock=PTHREAD_MUTEX_INITIALIZER;


//Checks to see if a number is prime
bool isPrime(long long int i)
{
	if (i <9)	
	{	
		if(i ==2 or i == 3)
		{	
			return true;
		}
		
	    for (int x=3; x <i;x+=2)
		{
			if (i %2 == 0)
      		{
		  		return false;
			}
		
			if (i % x == 0)
			{
        		return false;
        	}
		
    	}
    	return true;	
	}
	
	else
	{
	
    	for (int x=3; x <= sqrt(i);x+=2)
		{
			if (i %2 == 0)
      		{
		  		return false;
			}
		
			if (i % x == 0)
			{
        		return false;
        	}
		
    	}
    	return true;
	}
}


//Thread Function
void *my_thread (void *p)
	{
		long long int num = (int) p;
		long long int i;
		
		
		for(i=beginning+num;i<=ending;i+=nthreads)
		{
			
			if(i !=0 or i !=1)	//If number is 0 or 1 skip
			{
				if (isPrime(i) == true)
			
				{
					pthread_mutex_lock (&my_lock);	//Locks critical zone
					sum++;
					pthread_mutex_unlock (&my_lock);//Unlocks
				}
			}
		}
	}



int main(int argc, char *argv[])
	{
	
	int i;
	sum = 0;
	
	//Input Variables
	int beg = atoll(argv[1]);
	int end = atoll(argv[2]);
	long long int num_threads = atoll(argv[3]);

        
    if (beg == 0)
    {
        beg++;
    }
        
	//Links input variables to global
	beginning = beg;
	ending = end;
	nthreads = num_threads;

	
	pthread_t threads[num_threads];

	//Creates threads until set amount
	for (i = 1; i <= num_threads; ++i)
	{
		pthread_create (&threads[i-1], NULL, my_thread, (void *)i); 
	}
		
		//Starts threads
	for (i=1; i<=num_threads; ++i)
	{
		pthread_join (threads[i-1], NULL);	
	}
        
		
	cout<<"There are "<<sum<<" prime numbers! "<<endl;
	}
