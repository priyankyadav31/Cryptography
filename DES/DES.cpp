// Name: Priyank Yadav
// Roll no: 13MA20031
// Make sure to have DES.cpp and matrix.txt in the same folder

// Compile command: g++ DES.cpp
// Run command:  a.exe < matrix.txt


#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

typedef vector<int> vi;
vector<vector <int> > pc1(8, vi(7, 0));
vector<vector <int> > pc2(8,vi(6,0));
vector<vector <int> > ip(8,vi(8,0));
vector<vector <int> > ES(8,vi(6,0));
vector<vector <int> > P(8,vi(4,0));
vector<vector <int> > INV_IP(8,vi(8,0));
vector<vector <int> > S1(4,vi(16,0));
vector<vector <int> > S2(4,vi(16,0));
vector<vector <int> > S3(4,vi(16,0));
vector<vector <int> > S4(4,vi(16,0));
vector<vector <int> > S5(4,vi(16,0));
vector<vector <int> > S6(4,vi(16,0));
vector<vector <int> > S7(4,vi(16,0));
vector<vector <int> > S8(4,vi(16,0));

vector<bitset <48> >round_key(16);

// Function for reading entries from PC1 table
void read_pc1()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<7; j++)
		{
			cin >> pc1[i][j];
		}
	}

}

// Function for reading entries from PC2 table
void read_pc2()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<6; j++)
		{
			cin >> pc2[i][j];
		}
	}
}

// Function for reading entries from IP table
void read_ip()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			cin >> ip[i][j];
		}
	}
}

// Function for reading entries from EC expansion table
void read_ES()
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<6; j++)
		{
			cin >> ES[i][j];
		}
	}
}

// Function for reading entries from S table
void read_S()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S1[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S2[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S3[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S4[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S5[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S6[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S7[i][j];
	for(i=0;i<4;i++)
		for(j=0;j<16;j++)
			cin >> S8[i][j];
}

// Function for reading entries from P table
void read_P()
{
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<4;j++)
		{
			cin >> P[i][j];
		}
	}
}

// Function for reading entries from INV_P table
void read_INV_IP()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cin >> INV_IP[i][j];
		}
	}
}

// For calculating the value of the function f  [ Rn = Ln-1 + f(Rn-1,Kn) ]
bitset<32> f(bitset<32> R,int k)
{
	int m,n,x,y;
	string s1;
	bitset<48> temp;
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<6; j++)
		{
			temp[47-(i*6+j)] = R[32-ES[i][j]];
		}	
	}

	temp = (temp ^ round_key[k]);
	//cout << "temp : " << temp<<endl;
	for(int i=47;i>=0;i = i-6)
	{
		m = temp[i]*2 + temp[i-5];
		n = temp[i-1]*8 + temp[i-2]*4 + temp[i-3]*2 + temp[i-4];
		//cout << "m = " << m << "n = " << n <<" S[m][n]: " <<S[m][n]<<endl;
		if(i==47) x = S1[m][n];
		else if(i==41) x = S2[m][n];
		else if(i==35) x = S3[m][n];
		else if(i==29) x = S4[m][n];
		else if(i==23) x = S5[m][n];
		else if(i==17) x = S6[m][n];
		else if(i==11) x = S7[m][n];
		else if(i==5) x = S8[m][n];
        bitset<4> bin(x);
		s1 += bin.to_string();
	}
	bitset<32> SB(s1);
	//cout << "SB: " << SB << endl;
	
	bitset<32> temp2(SB);
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<4;j++)
		{
			SB[31-(i*4+j)] = temp2[32-P[i][j]];
		}
	}
	//cout << "SB: " << SB << endl;
	return SB;
}

// Functio for left shifting
void leftshift(bitset<28> &c , bitset<28> &d, int s)
{
	c = c << s | c >> (28-s);
	d = d << s | d >> (28-s);
}

// Defining DES cipher function
bitset<64> triple_des(bitset<64> msg,bitset<64> key)
{
	string s1,s2;
	
	bitset<56> k; // for storing keys of 56 bit size (permuted key)
	int i,j,l,m,n;

	//read_pc1();
	for(i=0; i<8; i++)
	{
		for(j=0; j<7; j++)
		{
			k[55-(i*7+j)] = key[64-pc1[i][j]];
		}
	}
	
	cout << "\nK+ : " << k << endl;

	bitset<56> divider1(0b00000000000000000000000000001111111111111111111111111111);
	bitset <28> c;
    bitset <28> d;
   

    d = bitset<28> ( (k & divider1).to_ulong() );
    c = bitset<28> ( ((k >> 28) & divider1).to_ulong() );
  
    //read_pc2();
   
    vector<int> r(16,2);
    
    r[0]=r[1]=r[8]=r[15] = 1;

    cout << "\n\n------------------   ROUND KEYS   -----------------------------\n\n";
    for(i=0;i<16;i++)
    {
    	leftshift(c,d,r[i]);
    	s1 = c.to_string();
    	s2 = d.to_string();

    	bitset <56> e(s1+s2);
    	
    	bitset<48> ki;
    	for(m = 0; m < 8; m++)
    	{
    		for(n = 0; n < 6; n++)
    		{
    			ki[47-(m*6+n)] = e[56-pc2[m][n]]; // i'th round key
    		}
    	}
    	round_key[i] = ki;
    	cout << "K" << i+1 << " : " << round_key[i] << endl << endl;
    }
    cout << "---------------------------------------------------------------\n\n";

    bitset<64> M;
    //read_ip();

    for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			M[63-(i*8+j)] = msg[64 - ip[i][j]];
		}
	}
    
    cout << "After Initial Permutation\n";
    cout << "M: " << M << endl;

    bitset<32> L0;
    bitset<32> R0;
    bitset<32> L1;
    bitset<32> R1;

    bitset<64> divider2(0b0000000000000000000000000000000011111111111111111111111111111111);

    R0 = bitset<32> ( (M & divider2).to_ulong() );
    L0 = bitset<32> ( ((M >> 32) & divider2).to_ulong() );
    cout << "---------------------------------------------------------------\n";
    cout << "L0: " << L0 << endl;
    cout << "R0: " << R0 << endl;

    //read_ES();
    //read_S();
    //read_P();

    for(i=0;i<16;i++)
    {
    	L1 = R0;
        R1 = L0 ^ (f(R0,i));
        L0 = L1;
        R0 = R1;
        cout << "\nL" << i+1 << ": " << L0 << endl;
        cout << "R" << i+1 << ": " << R0 << endl;
    }

    s1 = L0.to_string();
    s2 = R0.to_string();
    s2 = s2 + s1;

    bitset<64> cipher(s2);
    bitset<64> temp3(s2);

    //read_INV_IP();

    for(int i=0;i<8;i++)
    {
    	for(int j=0;j<8;j++)
    	{
    		cipher[63 - (i*8+j)] = temp3[64 - INV_IP[i][j]];
    	}
    }
    return cipher;
}

int main()
{
	string s1,s2;

	bitset<64> msg(string("0000000100100011010001010110011110001001101010111100110111101111"));   // Plain Text
    bitset<64> key(string("0001001100110100010101110111100110011011101111001101111111110001"));   // Key
    bitset<64> cipher;

    cout << "---------------------------------------------------------------\n";
    cout << "\nPLAIN TEXT:  " << msg << endl;
    cout << "\nKEY :        " << key << endl;

    read_pc1();
    read_pc2();
    read_ip();
    read_ES();
    read_S();
    read_P();
    read_INV_IP();

    cipher = triple_des(msg,key); // Calling DES
    
    cout << "---------------------------------------------------------------\n";
    cout << "\nPLAIN TEXT:  " << msg << endl;
    cout << "\nKEY :        " << key << endl;
    cout << "\nCIPHER TEXT: " << cipher << endl;

    
}
	
	

