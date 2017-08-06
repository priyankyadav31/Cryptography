#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <map>
#include <string>

using namespace std;

map <char,char> pi_s;
map <int,int> pi_p;
string plain,cipher,K = "00111010100101001101011000111111";

void map_pi_s()
{
	pi_s.insert(pair <char,char> ('0', 'E'));
	pi_s.insert(pair <char,char> ('1', '4'));
	pi_s.insert(pair <char,char> ('2', 'D'));
	pi_s.insert(pair <char,char> ('3', '1'));
	pi_s.insert(pair <char,char> ('4', '2'));
	pi_s.insert(pair <char,char> ('5', 'F'));
	pi_s.insert(pair <char,char> ('6', 'B'));
	pi_s.insert(pair <char,char> ('7', '8'));
	pi_s.insert(pair <char,char> ('8', '3'));
	pi_s.insert(pair <char,char> ('9', 'A'));
	pi_s.insert(pair <char,char> ('A', '6'));
	pi_s.insert(pair <char,char> ('B', 'C'));
	pi_s.insert(pair <char,char> ('C', '5'));
	pi_s.insert(pair <char,char> ('D', '9'));
	pi_s.insert(pair <char,char> ('E', '0'));
	pi_s.insert(pair <char,char> ('F', '7'));
}

void map_pi_p()
{
	pi_p.insert(pair <int,int> (1,1));
	pi_p.insert(pair <int,int> (2,5));
	pi_p.insert(pair <int,int> (3,9));
	pi_p.insert(pair <int,int> (4,13));
	pi_p.insert(pair <int,int> (5,2));
	pi_p.insert(pair <int,int> (6,6));
	pi_p.insert(pair <int,int> (7,10));
	pi_p.insert(pair <int,int> (8,14));
	pi_p.insert(pair <int,int> (9,3));
	pi_p.insert(pair <int,int> (10,7));
	pi_p.insert(pair <int,int> (11,11));
	pi_p.insert(pair <int,int> (12,15));
	pi_p.insert(pair <int,int> (13,4));
	pi_p.insert(pair <int,int> (14,8));
	pi_p.insert(pair <int,int> (15,12));
	pi_p.insert(pair <int,int> (16,16));
}

int main()
{  
	int lm,l,m=0,i,j;
	string temp_k,u,v;
	cin >> plain;
	lm = plain.length();

	map_pi_s();
	map_pi_p();

	for(i=0;i<1;i++)
	{
		temp_k = K.substr(m,16);
		bitset<16> _u = bitset<16>(plain) ^ bitset<16>(temp_k);
		cout << _u << endl;
		u = _u.to_string<char, string::traits_type, string::allocator_type>();
		//cout << u;
	}

return 0;

}