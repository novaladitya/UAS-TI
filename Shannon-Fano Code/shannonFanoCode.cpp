#include <iostream>
#include <vector>
#include <string.h>
using namespace std; 

// declare structure node 
struct node { 

	// for storing symbol 
	string sym; 

	// for storing probability or frquency 
	float pro; 
	int arr[20]; 
	int top; 
} p[20]; 

typedef struct node node; 

// function to find shannon code 
void shannon(int l, int h, node p[]) 
{ 
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0; 
	int i, k, j; 
	if ((l + 1) == h || l == h || l > h) { 
		if (l == h || l > h) 
			return; 
		p[h].arr[++(p[h].top)] = 0; 
		p[l].arr[++(p[l].top)] = 1; 
		return; 
	} 
	else { 
		for (i = l; i <= h - 1; i++) 
			pack1 = pack1 + p[i].pro; 
		pack2 = pack2 + p[h].pro; 
		diff1 = pack1 - pack2; 
		if (diff1 < 0) 
			diff1 = diff1 * -1; 
		j = 2; 
		while (j != h - l + 1) { 
			k = h - j; 
			pack1 = pack2 = 0; 
			for (i = l; i <= k; i++) 
				pack1 = pack1 + p[i].pro; 
			for (i = h; i > k; i--) 
				pack2 = pack2 + p[i].pro; 
			diff2 = pack1 - pack2; 
			if (diff2 < 0) 
				diff2 = diff2 * -1; 
			if (diff2 >= diff1) 
				break; 
			diff1 = diff2; 
			j++; 
		} 
		k++; 
		for (i = l; i <= k; i++) 
			p[i].arr[++(p[i].top)] = 1; 
		for (i = k + 1; i <= h; i++) 
			p[i].arr[++(p[i].top)] = 0; 

		// Invoke shannon function 
		shannon(l, k, p); 
		shannon(k + 1, h, p); 
	} 
} 

// Function to sort the symbols 
// based on their probability or frequency 
void sortByProbability(int n, node p[]) 
{ 
	int i, j; 
	node temp; 
	for (j = 1; j <= n - 1; j++) { 
		for (i = 0; i < n - 1; i++) { 
			if ((p[i].pro) > (p[i + 1].pro)) { 
				temp.pro = p[i].pro; 
				temp.sym = p[i].sym; 

				p[i].pro = p[i + 1].pro; 
				p[i].sym = p[i + 1].sym; 

				p[i + 1].pro = temp.pro; 
				p[i + 1].sym = temp.sym; 
			} 
		} 
	} 
} 

// function to display shannon codes 
void display(int n, node p[]) 
{ 
	int i, j; 
	cout << "Char | Probability | Shannon-Fano Code" << endl
		 << "-----|-------------|------------------"; 
	for (i = n - 1; i >= 0; i--) { 
		cout << "\n  " << p[i].sym << "  |   " << p[i].pro << "  |    "; 
		for (j = 0; j <= p[i].top; j++) 
			cout << p[i].arr[j]; 
	}
	cout << endl; 
} 

string sorting(string input){
	for(int i=0; i<input.length()-1; i++){
		for(int j=0; j<input.length()-i-1; j++){
			if(input[j] > input[j+1]){
				char temp = input[j];
				input[j] = input[j+1];
				input[j+1] = temp;
			}
		}
	}
	return input;
}

// Driver code 
int main() 
{  
	float total = 0;
	string input;
	cout << "Input text >> ";
	getline(cin, input);
	input = sorting(input);

	int i = 0,
		counterChar = 0,
		size = 1;
	char buffer = input[0];
	vector <char> chara;
	vector <int> freq;
	vector <float> prob;

	chara.push_back(input[0]);
	while(input[i] != '\0'){
		if(buffer != input[i]){
			buffer = input[i];
			chara.push_back(buffer);
			++size;
			freq.push_back(counterChar);
			counterChar = 0;
		}
		counterChar++;
		i++;
	}
	freq.push_back(counterChar);
	for(float f : freq){
	    prob.push_back(f/size);
	}
	char *character = chara.data();
	float *probability = prob.data();

	// Input symbols 
	for (int i = 0; i < size; i++) { 
        string a;
        a.push_back(character[i]);
		// Insert the symbol to node 
		p[i].sym += a; 
	} 

	// Input probability of symbols 
	for (int i = 0; i < size; i++) { 
		// Insert the value to node 
		p[i].pro = probability[i];
		total = total + p[i].pro; 
	} 

	p[i].pro = 1 - total; 

	// Sorting the symbols based on 
	// their probability or frequency 
	sortByProbability(size, p); 

	for (int i = 0; i < size; i++) 
		p[i].top = -1; 

	// Find the shannon code 
	shannon(0, size - 1, p); 

	// Display the codes 
	display(size, p); 
	return 0; 
} 

//https://www.geeksforgeeks.org/shannon-fano-algorithm-for-data-compression/
