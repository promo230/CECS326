#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h> 
/*
   n is the array size, w is the window size and pages is the list
   of pages.
 */
using namespace std;
void workingset(int n, int w, int pages[])
{
	/* This is the header line as shown in the homework assignment */
	printf("Time \t Size \t Set\n");

	/* DUMMY SAMPLE CODE, REMOVE! */
	/* This print shows how to compute the loop bounds. */
	//  printf("Do from %d to %d\n",w-1,n-1);

	/* This print confirms the parameter pass, it shows you how to line
	   things up with the headers.*/
//	printf("%d \t %d \t ",n,w);
	vector<int> v;
	for (int time=w-1;time<n;time++)
	{
		//Declare STL Vector
		
		//Set x = to current number in page
		int x = pages[time];
		//Loop to see if page is in window
		if(find(v.begin(), v.end(), x) != v.end()) {
			//Page is in window - do nothing
		} else {
			//Page not in window - Push back to vector
			v.push_back(pages[time]);
		}
		if(v.size() < 5){
			int size = v.size();
			printf("%d \t %d \t  ", time, size);
			for (int i =0; i < v.size();  ++i) {
        			printf("%d ", v[i]); 
			}
		printf("\n");
		}
		
//		printf("%d ",pages[time]);
	}
	printf("\n");

};

int main()
{
	int list1[] = {1,2,3,3,2,3,2,1,2,1,2,1,3,1,3,1,2,3,1};
	int list2[] = {1,2,3,3,4,4,5,3,3,2,1,2,1,2,3,4,5,3,2,4,2,4,2,2};
	/* notice the tricky way of getting the number of integers in the array */
	workingset(sizeof(list1)/sizeof(int),3,list1);
	workingset(sizeof(list2)/sizeof(int),4,list2);

	return 0;
};
