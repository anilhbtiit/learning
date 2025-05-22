#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <math.h>

using namespace std;
void print_binary(int num){
    for(int i=31;i>=0;i--) cout<<((num>>i)&1);
    cout<<endl;
}

bool isPowerOfTwo(int x)
{
  return (x /*to handle 0*/ && !(x & (x - 1)));
}

/*Given an integer n, any valid n-bit gray code sequence:  binary representation of the integers differs by exactly one bit.
Input: n = 2
Output: [0,1,3,2]
The binary representation of [0,1,3,2] is [00,01,11,10].
- 00 and 01 differ by one bit
- 01 and 11 differ by one bit
- 11 and 10 differ by one bit
- 10 and 00 differ by one bit
*/
vector<int> grayCode(int n)
{
   vector<int>v;
   for(int i=0 ;i<(1<<n);i++)
   v.push_back(i^(i>>1));
   return v;
}

int rev_grayCode (int g) {
 int n = 0;
 for (; g; g >>= 1)
   n ^= g;
 return n;
}

/* 
 *
maximum-xor-of-two-numbers-in-an-array

Logic: for a 32 bit number we have 32 bits in memory, so in order to
find the largest possible value of an XOR operation, the value of XOR
should have most of the bits set (i.e. 1) starting from the left to right

I have given code here Because i have used same concept Here.
When i am reading solution section i just not found any solution like this
most of them  just use tries  SO think it should be shared 
*/
    void solve(int target,vector<int>&nums,int &ans)
    {
        unordered_set<int>s;
        for(auto dig:nums)
        {  
          auto digit=((target&dig));
          if(s.count(digit^target)!=0)
          { 
            ans=target;   
            return ;
          }
          s.insert(digit);
        }
    }
    int findMaximumXOR(vector<int>& nums) 
    {
      int ans=0;
      for(int i=31;i>=0 ;i--)
        solve((ans| (1<<i)),nums,ans);
      return ans;
     
    }

//To find the minimum(x, y), we can use the expression y ^ ((x ^ y) & -(x < y)).
int findMin(int x, int y) {
    return y ^ ((x ^ y) & -(x < y));
}
 
int findMax(int x, int y) {
    return x ^ ((x ^ y) & -(x < y));
}

int turnOffKthBit(int n, int k) {
    return n & ~(1 << (k - 1));
}
int turnOnKthBit(int n, int k) {
    return n | (1 << (k - 1));
}
bool isKthBitSet(int n, int k) {
    return (n & (1 << (k - 1))) != 0;
}
int toggleKthBit(int n, int k) {
    return n ^ (1 << (k - 1));
}
int positionOfRightmostSetBit(int n)
{
    // if the number is odd, return 1
    if (n & 1) {
        return 1;
    }
    return log2(n & -n) + 1;
}
int countSetBits(int n)
{
    // `count` stores the total bits set in `n`
    int count = 0;
    while (n)
    {
        n = n & (n - 1);    // clear the least significant bit set
        count++;
    }
    return count;
}
int main() 
{
  print_binary(65);
  print_binary(97);
  cout << "\n16 is power of 2: " << (isPowerOfTwo(16) ? "Yes" : "No") << "\n";
	vector<int> graycode = grayCode(2);
	for(auto i:graycode)
		cout << i << " ";
	cout << "\n";
  //std::vector<int> nums = {2,3,4,5, 8};
  std::vector<int> nums = {4,5, 8};
  int maxXOR = findMaximumXOR(nums);
  cout << "\nmax XOR: " << maxXOR << "\n";
  std::vector<int> nums1 = {2,3,4,5, 8,6};
  int maxXOR1 = findMaximumXOR(nums1);
  cout << "\nmax XOR-1: " << maxXOR1 << "\n";
  std::vector<int> nums2 = {2,3,4,5, 8,6,7};
  int maxXOR2 = findMaximumXOR(nums2);
  cout << "\nmax XOR-2: " << maxXOR2 << "\n";
  cout << "\nMin of 4 and 5 is: " << findMin(4,5) << "\n";
  cout << "\nMax of 4 and 5 is: " << findMax(4,5) << "\n";
  cout << "\nTurn off 4th bit of 25: " << turnOffKthBit(25, 4) << "\n";
  cout << "\nTurn on 4th bit of 17: " << turnOnKthBit(17, 4) << "\n";
  cout << "\nIs 4th bit set of 17: " << isKthBitSet(17, 4) << "\n";
  cout << "\nToggle 4th bit of 17: " << toggleKthBit(17, 4) << "\n";
  cout << "\nPosition of right most set bit of 24 is: " << positionOfRightmostSetBit(24) << "\n";
  cout << "\nNumber of set bits of 17: " << countSetBits(17) << "\n";

}
