#include <iostream>
using namespace std;

int get(int array[], int row, int column) 
{
	int n = 0;
	for (int i = 0 ; i < row ; i++) n += i;
	return array[n+column];
}

void put(int array[], int row, int column, int input)
{
	int n = 0;
	for (int i = 0 ; i < row ; i++) n += i;
	array[n+column] = input;
}

int main()
{
	
}

class LinkList {
	public:
		//data...
		LinkList *next;
};

bool isSame(LinkList *L_head, LinkList *M_head) {
	LinkList *start_L = L_head;
	LinkList *start_M = M_head;
	int headsame = 0;
	do {
		if (start_L->data == M_head->data) {
			headsame = 1;
			break;
		}
		start_L = start_L->next;
	} while (start_L =! L_head);
	if (headsame) {
		do {
			if (start_L->data != start_M->data) return false;
			start_L = start_L->next;
			start_M = start_M->next;
		} while (start_L != L_head);
		return true;
	} else return false;
}

int main()
{
	LinkList L, M;
	LinkList *L_head, *M_head;
	//process L, M;

	if (isSame(L_head, M_head)) cout << "same";
	else cout << "different";
	return 0;
}

void swap(int *a, int *b) 
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void rearrange(int array[], int pos, int swapPos, int max)
{
	if (pos >= max || swapPos >= max) return;
	else if (array[pos]%2 != 0) {
		swap(&array[pos], &array[swapPos]);
		rearrange(array, pos, swapPos+1, max);
	} else
		rearrange(array, pos+1, pos+2, max);
}

int main() 
{
	int array[max];
	//....process array
	rearrange(array, 0, 1, max);
	int swapPos = 1;
	for (int i = 0 ; i < max ; i++) {
		if (array[i]%2 == 0) {
			swapPos = i + 2;
			continue;
		}
		else if (array[i]%2 != 2) {
			swap(array[i], array[swapPos]);
			swapPos++;
		}
	}

	return 0;
}