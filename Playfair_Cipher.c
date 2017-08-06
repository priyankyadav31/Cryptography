#include <stdio.h>
#include <string.h>

#define keyword "CHARLES"
char A[5][5];

// Function to calculate the encrypted value of the character from the matrix
void E_find(char a,char b,char *c,char *d)
{
	int i,j,r1,c1,r2,c2,count = 0;
	
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			if(A[i][j] == a)
			{
				r1 = i;
				c1 = j;
				++count;
			}
			else if(A[i][j] == b)
			{
				r2 = i;
				c2 = j;
				++count;
			}
			if(count == 2) break;
		}
		if(count == 2) break;
	}
	
	if(r1 == r2)
	{
		*c = A[r1][(c1+1)%5];
		*d = A[r1][(c2+1)%5]; 
	}
	else if(c1 == c2)
	{
		*c = A[(r1+1)%5][c1];
		*d = A[(r2+1)%5][c1];
	}
	else
	{
		*c = A[r1][c2];
		*d = A[r2][c1];
	}
}

//Function to split the plain text into pairs and encrypting it
int Encrypt(char plain[],char cipher[],int n)
{
	int i=0,flag = 1,k=0,l=0;
	char a,b,c,d,temp[100];
	while(i<n)
	{
		if(plain[i] == ' ') ++i;
		else
		{
			if(plain[i] == 'J') temp[k] = 'I';
			else  temp[k] = plain[i];
			++i;++k;
		}
	}
	
	i=0;

	while(i<k-1)
	{
		if(flag == 1)
		{
			if(temp[i] == temp[i+1])
			{
				a = temp[i];
				b = 'X';
				flag = 0;
				++i;
			}
			else
			{
				a = temp[i];
				b = temp[i+1];
				i += 2;
			}
		}
		else
		{
			a = 'X';	
			b = temp[i];
			flag = 1;
			++i;
		}
    
		E_find(a,b,&c,&d);
		cipher[l++] = c;
		cipher[l++] = d;
	}

	if(i == k-1)
	{
		if(flag == 1)
		{
			a = temp[i];
			b = 'X';
			flag = 0;
			++i;
		}
		else
		{
			a = 'X';
		    b = temp[i];
		    flag = 1;
		    ++i;
		}
		E_find(a,b,&c,&d);
	    cipher[l++] = c;
		cipher[l++] = d;

	}
	return l;
}

// Function to print the condtructed matrix
void print_matrix ()
{
	int i,j;
	printf("--------------------------------------------\n");
	printf("Playfair matrix is : \n");
	for(i = 0;i<5;i++)
	{
		for(j = 0;j <5;j++)
		{
			printf("%c  ",A[i][j]);
		}
		printf("\n");
	}
	printf("--------------------------------------------\n");
}

void main()
{
	char c,plain[100],cipher[100];
	int i,j,k=0,l,temp = 0,m,n,cl = 0;
	printf("Enter the plain text\n");
	fgets(plain,100,stdin);             // Reading the plain text as a string
	n = strlen(plain)-1;                // Calculating length of the plain text

	for(i=0;i<n;i++)
		plain[i] = toupper(plain[i]);   // Changing lowercase into uppercase

	l = strlen(keyword);
	
	char alph[25-l];
	for(i = 0;i < 26; i++)
	{
		c = (char)(65+i);
		if(c != 'J' && strchr(keyword,c) == NULL)
			alph[k++] = c;
	}

	k = 0;temp = 0;

	// Building matrix [5X5]
	for(i=0;i<5;i++)
	{
		for(j = 0;j<5;j++)
		{
			if(k < l)
			{
				A[i][j] = keyword[k];
				++k;
			}
			else
			{
				A[i][j] = alph[temp++];
			}
		}
	}

	print_matrix();                        // Printing matrix
	
	cl = Encrypt(plain,cipher,n);
	printf("Cipher text is : %s\n",cipher);
}