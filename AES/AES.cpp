// Name: Priyank Yadav
// Roll no: 13MA20031
// Make sure to have AES.cpp and table.txt in the same folder

// Compile command: g++ AES.cpp
// Run command:  a.exe < table3.txt

#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

map<char,int> m;

typedef vector<int> v1;
typedef vector< bitset<8> > v2;

vector<vector <bitset<8> > > M2(4,v2(4));    
vector<vector <bitset<8> > > M3(4,v2(4,0));
vector<vector <bitset<8> > > S(16,v2(16));

vector<vector <bitset<8> > > M1(4,v2(4));
vector<vector <bitset<8> > > K0(4,v2(4));     // Round key2 matrix
vector<vector <bitset<8> > > merger(4,v2(8)); // Used in Add round Key operation
vector<vector <bitset<8> > > K1(4,v2(4));     // Round key1 matrix

vector<vector <int> > MCM(4,v1(4));           // Mixed column matrix

// Funtion for converting hexadecimal values to bitset<8>
bitset<8> hex2bit(string x)
{
	bitset<4> a;
	bitset<4> b;
	if(x[0] >= 'a' && x[0] <= 'f')
	{
		bitset<4> temp1(m[x[0]]);
		a = temp1;
	}
	else
	{
		bitset<4> temp1(x[0]-'0');
		a = temp1;
	}
	if(x[1] >= 'a' && x[1] <= 'f')
	{
		bitset<4> temp1(m[x[1]]);
		b = temp1;
	}
	else
	{
		bitset<4> temp1(x[1]-'0');
		b = temp1;
	}
	bitset<8> c(0);
	for(int i=0;i<8;i++)
	{
		if(i<4) c[i] = b[i];
		else c[i] = a[i-4];
	}
	return(c);
}

// Function to read S-Box matrix
void read_S() 	
{
	string x;
	for(int i=0;i<16;i++)
		for(int j = 0;j<16;j++)
		{
			cin >> x;
			S[i][j] = hex2bit(x);
		}
}

// Function to read MCM matrix for galois field operation
void read_MCM()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cin >> MCM[i][j];
}

void print_S()
{
	for(int i =0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			cout << S[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_M1()
{
	for(int i =0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout << M1[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_M3()
{
	for(int i =0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout << M3[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_MCM()
{
	for(int i =0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout << MCM[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_K0()
{
	for(int i =0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout << K0[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_K1()
{
	for(int i =0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout << K1[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

// Step 0 : ADD ROUND KEY
void add_round_key()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			M1[i][j] ^= K0[i][j];
		}
	}
}

// Step 1 : SUBSTITUTION OF BYTES
void sub_byte()
{
	int r,c;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			bitset<4> temp1(0);
			for(int k=4;k<=7;k++) temp1[k-4] = (M1[i][j])[k];
			r = (int) (temp1.to_ulong());
		    for(int k=0;k<4;k++) temp1[k] = (M1[i][j])[k];
		    c = (int) (temp1.to_ulong());
		    M1[i][j] = S[r][c];
		}
	}
}

// Step 2 : SHIFT ROW OPERATION
void shift_row()
{
	int temp,l;
	for(int i = 0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			l = (j-i)%4;
			if(l < 0) l += 4;
			M2[i][l] = M1[i][j];
		}
	}
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			M1[i][j] = M2[i][j];
}

// Matrix multiplication
bitset<8> mul(int x,bitset<8> y)
{
	bool flag = 0;
	bitset<8> z = y;
	bitset<8> w(string("00011011"));
	if(x == 1) return y;
	else
	{
		if(z[7] == 1) flag = 1;
		z = z << 1;
		if(flag == 1) z ^= w;
		if(x == 3) z ^= y;
	}
	return z;

}

// Step 3 : MIXING OF COLUMN
void Mix_col()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				M3[i][j] ^= mul(MCM[i][k],M1[k][j]);
			}
		}
	}
	for(int i=0;i<4;i++)
		for(int j = 0;j<4;j++)
			M1[i][j] = M3[i][j];
}

int main()
{
	string plain,key,cipher,s1,s2;
	int k=0;
	plain = "Two One Nine Two";
	key =   "Thats my Kung Fu";

	cout << "\nInput Text : " << plain << endl;
	cout << "\nInput Key : " << key << endl;

    int l = plain.length();
    
    for(int i=97;i<=102;i++)
    	m.insert(make_pair(char(i),i-87));

	read_S();
	read_MCM();

	k = 0;
	for(int j=0;j<4;j++)
	{
		for(int i=0;i<4;i++)
		{
			bitset<8> temp1(int(plain[k]));
			//cout << plain[k] << " " << temp1 << endl;
			M1[i][j] = temp1;
			bitset<8> temp2(int(key[k]));
			K0[i][j] = temp2;
			++k;
		}
	}
	
	cout << "-----------------------------------------------------------------------\n\n";
	cout << " Initial Matrix for Plain Text : \n\n";
	print_M1();
	cout << "-----------------------------------------------------------------------\n\n";
	cout << " Initial Matrix for Input Key : \n\n";
	print_K0();
	cout << "-----------------------------------------------------------------------\n\n";

	cout << " Adding Round Key : \n\n";
	add_round_key();
	print_M1();
	cout << "-----------------------------------------------------------------------\n\n";

    cout << " Substitution Bytes : \n\n";
	sub_byte();
	print_M1();
    cout << "-----------------------------------------------------------------------\n\n";

    cout << " Shift Row : \n\n";
	shift_row();
	print_M1();
	cout << "-----------------------------------------------------------------------\n\n";

    cout << " Mix Columns : \n\n";
	Mix_col();
	print_M1();
	cout << "-----------------------------------------------------------------------\n\n";

    // Step 4 : ADD ROUND KEY 
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			merger[i][j] = K0[i][j];
		}

    vector<bitset<8> > temp1(4);
    
    bitset<8> temp;
    int r,c;
	for(k=4;k<8;k++)
	{
		if(k == 4)
		{
			for(int i=0;i<4;i++)
		    {
		    	l = (i-1)%4;
			    if(l<0) l += 4;
			    temp1[l] = merger[i][k-1]; 
		    }
		    for(int i=0;i<4;i++)
		    {
		    	bitset<4> temp2(0);
			    for(int j=4;j<=7;j++) temp2[j-4] = (temp1[i])[j];
			    r = (int) (temp2.to_ulong());
		        for(int j=0;j<4;j++) temp2[j] = (temp1[i])[j];;
		        c = (int) (temp2.to_ulong());
		        temp1[i] = S[r][c];
		    }
		    bitset<8> temp2(1);
		    temp1[0] ^= temp2;
		}
		else
		{
			for(int i=0;i<4;i++)
			{
				temp1[i] = merger[i][k-1];
			}
		}
		for(int i=0;i<4;i++)
		{
			temp1[i] ^= merger[i][k-4]; 
			merger[i][k] = temp1[i];
		}
	}

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			K1[i][j] = merger[i][j+4];
		}
	}
    
    cout << " Add Round Key : \n\n";
	print_K1();
    cout << "-----------------------------------------------------------------------\n\n";

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			M1[i][j] ^= K1[i][j];
		}
	}
  
	cout << " AES output after round 1 : \n\n" << "Cipher Text: ";
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cout << M1[i][j] << " ";
}