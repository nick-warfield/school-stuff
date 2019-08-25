// Nicholas Warfield
// Comp 222 - Computer Organization - 2:00PM T/R
// due 4/4/19
// std=c++11

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void CheckCode(const bool oddParity)
{
	string code;
	cout << "Enter the Hamming code: ";
	cin >> code;
	vector<bool> bits, pBits, calcBits;

	for (auto c : code) { bits.push_back(c - '0'); }

	for (int i = 1; i <= bits.size(); i *= 2)
	{
		pBits.push_back(bits[bits.size() - i]);

		int oneSum = 0;
		for (int j = i; j < bits.size(); j += i)
		{
			for (int k = j + 1; k < j + i; k++)
			{
				if (bits[bits.size() - k]) { oneSum++; }
			}
		}

		calcBits.push_back((oneSum % 2 == 0) == oddParity);
	}

	cout << "Orig parity:";
	for (auto i : pBits) { cout << '\t' << i; }
	
	cout << "\nNew parity:";
	for (auto i : calcBits) { cout << '\t' << i; }

	cout << "\nDiffernce:";
	int badBit = 0;
	for (int i = 0; i < pBits.size(); i++)
	{
		calcBits[i] = (pBits[i] - calcBits[i]) * -1;
		cout << '\t' << calcBits[i];
		if (calcBits[i] == 1) { badBit += pow(2, i); }
	}

	cout << endl;
	if (badBit != 0)
	{
		badBit = bits.size() - badBit;
		bits[badBit] = -1 * bits[badBit] + 1;
		cout << "There is an error at bit " << badBit;
		cout << "\nThe correct code is: ";
		for (auto i : bits) { cout << i; }
		cout << endl;
	}
	else
	{
		cout << "There is no error\n";
	}
};

bool EnterParams(void)
{
	bool oddParity;
	char toss;
	cout << "Enter the maximum length of the Hamming code: ";
	cin >> toss;
	cout << "Enter the parity (0 = even, 1 = odd): ";
	cin >> oddParity;
	return oddParity;
};

int menu(void)
{
	cout << "1) Enter Parameters\n";
	cout << "2) Check Hamming Code\n";
	cout << "3) Quit Program\n";
	cout << "> ";

	int input;
	cin >> input;
	return input;
};

int main(void)
{
	bool exit = false;
	bool oddParity;

	while (!exit)
	{
			switch (menu())
			{
					case 1: oddParity = EnterParams();
							break;
					case 2: CheckCode(oddParity);
							break;
					case 3: exit = true;
							break;
					default:
							cout << "Invalid Input\n";
							break;
			}
	}

	return 0;
};
