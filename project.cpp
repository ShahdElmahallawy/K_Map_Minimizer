#include <bits/stdc++.h>
using namespace std;
//A struct K_Map that includes the decimal and binary representations of the elements and the truth value
struct k_Map
{
    int decimal;
    string binary;
    int map;//The truth value 0 or 1 that appears in the map
};
//The vectors and arrays used in the program
vector<k_Map> vec1,vec2,vec3,vec4,vec5,primeimplicant;
vector<vector<k_Map>> allPrimeImplicants;
k_Map kmap[2][4];
//The Functions used in the program
void binaryK
(vector<vector<k_Map>>& kmap);
vector<int> readingMinterms();
void generatingKMap(const vector<int>&minterms);
void findingimplicants(vector<int> minterms);
void binaryKmap();
void booleanexpression();
vector<k_Map> maxVector(vector<k_Map>&vec1,vector<k_Map>&vec2,vector<k_Map>&vec3,vector<k_Map>&vec4,vector<k_Map>&vec5);
void printkmap();
void decimalkmap();

int main()
{
    vector<int> minterms = readingMinterms();
    //In case the number of minterms = 8, we output directly F = 1
    if(minterms.size() == 8)
    {
        for(int i = 0; i<2; i++)
            for(int j = 0; j<4; j++)
                kmap[i][j].map = 1;
        printkmap();
        cout<<"F = 1 "<<endl;
        return 0;
    }
    generatingKMap(minterms);
    binaryKmap();
    //IN case the minterm = 0, we output F =0
    if(minterms.size() == 0)
    {
        cout<<"F = 0 "<<endl;
        return 0;
    }
    findingimplicants(minterms);
    booleanexpression();

    return 0;
}
//A function that reads the minterms from the user as decimal numbers
vector<int> readingMinterms()
{
    //Taking the input from the user
    int n;
    cout<<"Enter the number of minterms "<<endl;
    cin>>n;
    //Creating the vector to store all the entered minterms
    vector<int> minterms(n);
    //In case the number of minterms = 8, we return and output F = 1 immediately
    if(n==8)
        return minterms;
    //Otherwise, we take the inputs from teh use
    int temp;
    //Validitating the minterms
    for(int i = 0; i<n; i++)
    {
        do
        {
            cout<<"Please enter a valid minterm "<<i+1<<endl;
            cin>>temp;
        } while (temp<0 || temp>7);
            minterms[i] = temp;
    }
    cout<<endl;

    return minterms;
}
//A function that prints the k_map
void printkmap()
{
    cout<<"     3_variable_K_Map "<<endl;
    cout<<"--------------------------------"<<endl;
    cout<<endl;
    cout<<"A/BC  | 00  | 01  | 11  | 10 "<<endl;
    cout<<"--------------------------------"<<endl;
    for(int i = 0; i<2; i++)
    {
        cout<<i<<"     ";
        for(int j = 0; j<4; j++)
        {
            cout<<"|"<<kmap[i][j].map<<"    ";
        }
        cout<<endl;
    }

}
//Generating the kmap
void generatingKMap(const vector<int>&minterms)
{
        //We first set the truth values of all the elements in the map to be zero
        for(int i = 0; i<2; i++)
            for(int j = 0; j<4; j++)
                kmap[i][i].map = 0;
        //Setting the kmap according the entered minterms
        for(int i = 0; i<minterms.size(); i++)
        {
            switch(minterms[i])
            {
                case 0:
                    kmap[0][0].map = 1;
                    break;
                case 1:
                    kmap[0][1].map = 1;
                    break;
                case 2:
                    kmap[0][3].map = 1;
                    break;
                case 3:
                    kmap[0][2].map = 1;
                    break;
                case 4:
                    kmap[1][0].map = 1;
                    break;
                case 5:
                    kmap[1][1].map = 1;
                    break;
                case 6:
                    kmap[1][3].map = 1;
                    break;
                case 7:
                    kmap[1][2].map = 1;
                    break;
            }
        }
        decimalkmap();
        printkmap();
}
//Generating the decimal representation
void decimalkmap()
{
    kmap[0][0].decimal = 0;
    kmap[0][1].decimal = 1;
    kmap[0][2].decimal = 3;
    kmap[0][3].decimal = 2;
    kmap[1][0].decimal = 4;
    kmap[1][1].decimal = 5;
    kmap[1][2].decimal = 7;
    kmap[1][3].decimal = 6;
}
//Generating the binary representation
void binaryKmap()
{
	kmap[0][0].binary = "000";
	kmap[0][1].binary = "001";
	kmap[0][2].binary = "011";
	kmap[0][3].binary = "010";
	kmap[1][0].binary = "100";
	kmap[1][1].binary = "101";
	kmap[1][2].binary = "111";
	kmap[1][3].binary = "110";
}
//The main algorithm that finds all the implicants in the kmap
void findingimplicants(vector<int> minterms)
{
    //The five cases we have
for(int i = 0; i<2; i++)
{
    for(int j = 0; j<4; j++)
    {
        //If the cell is 1
        if(kmap[i][j].map == 1)
        {
            vec1.push_back(kmap[i][j]);
            //If two cells in a column are 1
            if(kmap[i][(j+1)%4].map == 1)
            {
                vec2.push_back(kmap[i][j]);
                vec2.push_back(kmap[i][(j+1)%4]);
            }
            //If two cells in a row are 1
            if(kmap[(i+1)%2][j].map == 1)
            {
                vec3.push_back(kmap[i][j]);
                vec3.push_back(kmap[(i+1)%2][j]);
            }
            //If four cells in a square are equal 1
            if(kmap[i][(j+1)%4].map==1&&kmap[(i+1)%2][j].map==1&&kmap[(i+1)%2][(j+1)%4].map==1)
            {
                vec4.push_back(kmap[i][j]);
                vec4.push_back(kmap[i][(j+1)%4]);
                vec4.push_back(kmap[(i+1)%2][j]);
                vec4.push_back(kmap[(i+1)%2][(j+1)%4]);
            }
            //If four cells in a row = 1
            if(kmap[i][(j+1)%4].map==1&&kmap[i][(j+2)%4].map==1&&kmap[i][(j+3)%4].map==1)
            {
                vec5.push_back(kmap[i][j]);
                vec5.push_back(kmap[i][(j+1)%4]);
                vec5.push_back(kmap[i][(j+2)%4]);
                vec5.push_back(kmap[i][(j+3)%4]);
            }
            //Take the maximum of implicant(the primeimplicant) of all the five cases
            primeimplicant = maxVector(vec1,vec2,vec3,vec4,vec5);
            //We push back all the implicants into a vector of vector
            allPrimeImplicants.push_back(primeimplicant);
            primeimplicant.clear();
        }
        vec1.clear();
        vec2.clear();
        vec3.clear();
        vec4.clear();
        vec5.clear();
    }
}

    //Sorting the implicants by size
    for(int i = 0; i<allPrimeImplicants.size();i++)
    {
        for(int j = 0; j<allPrimeImplicants.size()-1;j++)
        {
            if(allPrimeImplicants[j].size()>allPrimeImplicants[j+1].size())
            {
                vector<k_Map> temp = allPrimeImplicants[j];
                allPrimeImplicants[j] = allPrimeImplicants[j+1];
                allPrimeImplicants[j+1] = temp;
            }
        }
    }
    //Sorting the minterms of each implicant ascendigly
    for(int k = 0; k<allPrimeImplicants.size();k++)
    {
         for(int i = 0; i<allPrimeImplicants[k].size();i++)
        {
            for(int j = 0; j<allPrimeImplicants[k].size()-1;j++)
            {
                if(allPrimeImplicants[k][j].decimal>allPrimeImplicants[k][j+1].decimal)
                {
                    int temp = allPrimeImplicants[k][j].decimal;
                    allPrimeImplicants[k][j].decimal = allPrimeImplicants[k][j+1].decimal;
                    allPrimeImplicants[k][j+1].decimal = temp;
                }
            }
        }
    }

    //Removing duplicated and included implicants to get
    int counter = 0;
    int s = allPrimeImplicants.size();

	for (int i = 0; i < s; i++)
		for (int k = i+1; k < s; k++)
		{
			for (int j = 0; j < allPrimeImplicants[i].size(); j++)
			{
				for (int N = 0; N < allPrimeImplicants[k].size(); N++)
				{
				    //We check if a given implicant is a duplicate or a subset of another implicant
					if (allPrimeImplicants[i][j].decimal == allPrimeImplicants[k][N].decimal)
						counter++;
				}
			}

				if (counter == allPrimeImplicants[i].size())

					allPrimeImplicants.erase(allPrimeImplicants.begin() + i);
				counter = 0;
		}

}
//A function that takes 5 vectors and returns the maximum of them
vector<k_Map> maxVector(vector<k_Map>&vec1,vector<k_Map>&vec2,vector<k_Map>&vec3,vector<k_Map>&vec4,vector<k_Map>&vec5)
{
    //Taking the sizes of each vector and store it into an array of capcities
    int cap[5];
	cap[0] = vec1.size();
	cap[1] = vec2.size();
	cap[2] = vec3.size();
	cap[3] = vec4.size();
	cap[4] = vec5.size();

	int max = -1;
	int number;
	for (int i = 0; i < 5; i++)
	{
		if (cap[i] > max)
		{
			max = cap[i];
			number = i + 1;
		}
	}
	switch(number)
    {
    case 1:
        return vec1;
    case 2:
        return vec2;
    case 3:
        return vec3;
    case 4:
        return vec4;
    case 5:
        return vec5;
    }
}
//A function that takes the input as binary representation of the implicant and outputs the corresponding
//variables in A, B, C (The Simplified boolean expression)
void booleanexpression()
{
    //The string that holds final expression
    string F;
    //A vector of string that stores the binary representation of all the minterms
	vector<string> minterms;
	string tmp = "";
	int num;
	for (int i = 0; i < allPrimeImplicants.size(); i++)
	{
		num = allPrimeImplicants[i].size();
		minterms.resize(num);
		for (int j = 0; j < num; j++)
			minterms[j] = allPrimeImplicants[i][j].binary;
		int temp = 0;
		//Arriving at the boolean expression from the binary representation of the minterms
		for (int n = 0; n < 3; n++)
		{
			int m = 0;
			for (int k = 1; k < num; k++)
			{
				if (minterms[m][n] == minterms[k][n])
					temp++;
			}
			if (temp == num - 1)
			{
				if (minterms[0][n] == '0')
					tmp = tmp + char(n + 65) + "'";
				else if (minterms[0][n] == '1')
                    tmp = tmp + char(n + 65);
			}
			temp = 0;
		}
		tmp += " + ";
	}
	F = tmp;
	F = F.erase(F.size() - 2);
	cout<<"F = "<<F<<endl;
}
