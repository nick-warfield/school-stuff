#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace std;

struct Performance
{
	int ClockSpeed = 0;
	vector<int> CPI;
	vector<int> InstructionCount;
};

void PrintLine(void)
{
	for (int i = 0; i < 25; i++) { cout << '-'; }
	cout << endl;
}

void EnterParams(Performance& perf)
{
	perf.CPI.clear();
	perf.InstructionCount.clear();

	cout << "Enter the number of instruction classes: ";
	int count;
	cin >> count;
	cout << "Enter the frequency of the machine (MHz): ";
	cin >> perf.ClockSpeed;

	int input;
	for (int i = 0; i < count; i++)
	{
		cout << "\nEnter the CPI of class " << i + 1 << ": ";
		cin >> input;
		perf.CPI.push_back(input);
		cout << "Enter the instruction count of class " << i + 1
			<< " (in millions): ";
		cin >> input;
		perf.InstructionCount.push_back(input);
	}
}

void PrintParams(const Performance& perf)
{
	PrintLine();
	cout << "|Class\t|CPI\t|Count\t|\n";
	PrintLine();

	for (int i = 0; i < perf.CPI.size(); ++i)
	{
		cout << "|" << i + 1 << "\t|" << perf.CPI[i] << "\t|"
			<< perf.InstructionCount[i] << "\t|\n";
		PrintLine();
	}
}

void PrintPerf(const Performance& perf)
{
	float ave = 0, time = 0, mips = 0;
	int totalInstructions = 0;

	for (int i = 0; i < perf.InstructionCount.size(); ++i)
	{
		totalInstructions += perf.InstructionCount[i];
	}

	for (int i = 0; i < perf.CPI.size(); ++i)
	{
		ave += perf.CPI[i] * perf.InstructionCount[i];
	}

	time = (ave * 1000) / perf.ClockSpeed;
	ave /= totalInstructions;
	mips = perf.ClockSpeed / ave;

	cout << fixed << setprecision(2);
	PrintLine();
	cout << "|Performance\t|Value\t|\n";
	PrintLine();
	cout << "|Average CPI\t|" << ave << "\t|\n";
	PrintLine();
	cout << "|CPU Time (ms)\t|" << time << "\t|\n";
	PrintLine();
	cout << "|MIPS\t\t|" << mips << "\t|\n";
	PrintLine();
}

int MainPrompt(void)
{
	cout << endl;
	cout << "Performance Assessment Program:\n";
	PrintLine();
	cout << "1) Enter Parameters\n";
	cout << "2) Print Table of Parameters\n";
	cout << "3) Print Table of Performance\n";
	cout << "4) Exit Program\n\n";
	cout << "Enter Selection: ";

	int input;
	cin >> input;
	PrintLine();
	cout << endl;
	return input;
}

int main(void)
{
	bool exit = false;
	unique_ptr<Performance> params = make_unique<Performance>();
	while(!exit)
	{
		switch (MainPrompt())
		{
			case 1: EnterParams(*params); break;
			case 2: PrintParams(*params); break;
			case 3: PrintPerf(*params); break;
			case 4:	exit = true; break;
		}
	}

	return 0;
}
