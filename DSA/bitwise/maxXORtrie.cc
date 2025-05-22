#include <iostream>

using namespace std;

class Node {
public:
	Node* one;
	Node* zero;
};

class trie {
	Node* root;

public:
	trie() { root = new Node(); }

	void insert(int n)
	{
		Node* temp = root;
		for (int i = 31; i >= 0; i--) {
			int bit = (n >> i) & 1;
			if (bit == 0) {
				if (temp->zero == NULL) {
					temp->zero = new Node();
				}
				temp = temp->zero;
			}
			else {
				if (temp->one == NULL) {
					temp->one = new Node();
				}
				temp = temp->one;
			}
		}
	}

	int max_xor_helper(int value)
	{
		Node* temp = root;
		int current_ans = 0;

		for (int i = 31; i >= 0; i--) {
			int bit = (value >> i) & 1;
			if (bit == 0) {
				if (temp->one) {
					temp = temp->one;
					current_ans += (1 << i);
				}
				else {
					temp = temp->zero;
				}
			}
			else {
				if (temp->zero) {
					temp = temp->zero;
					current_ans += (1 << i);
				}
				else {
					temp = temp->one;
				}
			}
		}
		return current_ans;
	}

	int max_xor(int arr[], int n)
	{
		int max_val = 0;
		insert(arr[0]);
		for (int i = 1; i < n; i++) {
			max_val = max(max_xor_helper(arr[i]), max_val);
			insert(arr[i]);
		}
		return max_val;
	}
};

int main()
{
	int input[] = { 25, 10, 2, 8, 5, 3 };
	int n = sizeof(input) / sizeof(int);
	trie t;
	cout << t.max_xor(input, n) << "\n";

	return 0;
}

