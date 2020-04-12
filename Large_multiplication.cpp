#include<iostream>
using namespace std;

void reverse(string &a, const int &n)
{
    for(int i=0; i<n/2; ++i)
        swap(a[i], a[n-i-1]);
}

string findSum(string str1, string str2)
{
    // Before proceeding further, make sure length
    // of str2 is larger.
    if (str1.length() > str2.length())
        swap(str1, str2);

    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();

    // Reverse both of strings
    reverse(str1, n1);
    reverse(str2, n2);

    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');

        // Calculate carry for next step
        carry = sum/10;
    }

    // Add remaining digits of larger number
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    // Add remaining carry
    if (carry)
        str.push_back(carry+'0');

    // reverse resultant string
    reverse(str, str.size());

    return str;
}
// Returns true if str1 is smaller than str2.
bool isSmaller(string str1, string str2)
{
	// Calculate lengths of both string
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2)
	return true;
	if (n2 < n1)
	return false;

	for (int i=0; i<n1; i++)
	if (str1[i] < str2[i])
		return true;
	else if (str1[i] > str2[i])
		return false;

	return false;
}

// Function for find difference of larger numbers
string findDiff(string str1, string str2, bool &sign)
{
	// Before proceeding further, make sure str1
	// is not smaller
	if (isSmaller(str1, str2)){
        sign = true;
		swap(str1, str2);
	}
	// Take an empty string for storing result
	string str = "";

	// Calculate length of both string
	int n1 = str1.length(), n2 = str2.length();

	// Reverse both of strings
	reverse(str1, n1);
	reverse(str2,n2);

	int carry = 0;

	// Run loop till small string length
	// and subtract digit of str1 to str2
	for (int i=0; i<n2; i++)
	{
		// Do school mathematics, compute difference of
		// current digits

		int sub = ((str1[i]-'0')-(str2[i]-'0')-carry);

		// If subtraction is less then zero
		// we add then we add 10 into sub and
		// take carry as 1 for calculating next step
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}

	// subtract remaining digits of larger number
	for (int i=n2; i<n1; i++)
	{
		int sub = ((str1[i]-'0') - carry);

		// if the sub value is -ve, then make it positive
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}

	// reverse resultant string
	reverse(str,str.size());

	return str;
}
int makeEqualLength(string &str1, string &str2)
{
	int len1 = str1.size();
	int len2 = str2.size();
	if (len1 < len2)
	{
		for (int i = 0 ; i < len2 - len1 ; i++)
			str1 = '0' + str1;
		return len2;
	}
	else if (len1 > len2)
	{
		for (int i = 0 ; i < len1 - len2 ; i++)
			str2 = '0' + str2;
	}
	return len1; // If len1 >= len2
}

// The main function that adds two bit sequences and returns the addition
string subtract_string(string first, string second, bool &sign)
{
	// make the lengths same before adding
	makeEqualLength(first, second);
    return findDiff(first, second, sign);
}

// A utility function to multiply single bits of strings a and b
string multiplyiSingleBit(string &a, string &b)
{
    int val = (a[0] - '0')*(b[0] - '0');
    string ans="";
    while(val)
    {
        ans.push_back(val%10 + '0');
        val/=10;
    }
    reverse(ans, ans.length());
    return  ans;
}

string ten_mul(string str, int power)
{
    for(int i=0; i<power; ++i)
        str.push_back('0');
    return str;
}
string multiply(string &A, string &B)
{
	// Find the maximum of lengths of x and Y and make length
	// of smaller string same as that of larger string
	int n = makeEqualLength(A, B);

	// Base cases
	if (n == 0) return 0;
	if (n == 1) return multiplyiSingleBit(A, B);

	int fh = n/2; // First half of string, floor(n/2)
	int sh = (n-fh); // Second half of string, ceil(n/2)

	string p = A.substr(0, fh);
	string q = A.substr(fh, sh);

	// Find the first half and second half of second string
	string r = B.substr(0, fh);
	string s = B.substr(fh, sh);

	// Recursively calculate the three products of inputs of size n/2
	string pr = multiply(p,r);
	string qs = multiply(q, s);
	//trace(pr, qs);

	bool sign1 = false;
	string q_p = subtract_string(q, p, sign1);

	bool sign2 = false;
	string s_r = subtract_string(s, r, sign2);

	bool add = false;
	if((sign1 && !sign2) || (!sign1 && sign2))
        add = true;

	string q_ps_r = multiply(q_p, s_r);

	string X = ten_mul(pr, 2*sh);
	string Y1 = findSum(pr, qs);

	//trace(q_ps_r, X, Y1);
	sign1 = false;

	if(add)
        Y1 = findSum(Y1, q_ps_r);
    else
        Y1 = subtract_string(Y1, q_ps_r, sign1);

    //trace(Y1);

    string Y = ten_mul(Y1, sh);

//    assert(!sign1);
    string X_Y = findSum(X, Y);

    string ans = findSum(X_Y, qs);

	return ans;
}

int main(int argc, char** argv)
{
ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
 //   freopen("C:\\Users\\shubham.1232\\Documents\\in.c","r",stdin);
   // bool s = false;
    //cout<<subtract_string("4", "7", s);
    //trace(s);
	int T;
	cin>>T;
	string ans;
	for(int test = 1; test <= T; ++test)
    {
        string a, b;
        cin >> a >> b;
        string ans = multiply(a, b);
        int n = ans.size(), i = 0;
        while(i < n && ans[i] == '0')
            ++i;
        for(; i<n; ++i)
            cout<<ans[i];
        cout <<"\n";

    }
	return 0;//Your program should return 0 on normal termination.
}
