#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

struct Line
{
	int Tag;
	vector<int> Block;
	Line(int size) : Tag(-1)
	{
		while (size != 0)
		{
			Block.push_back(0);
			size--;
		}
	}
};

class Memory
{
	public:
		Memory(int discSize, int cacheSize, int blockSize)
		{
			offsetMax = blockSize;
			tagMax = discSize / cacheSize;
			lineMax = discSize / blockSize / tagMax;

			while (discSize != 0)
			{
				disc.push_back(discSize);
				discSize--;
			}
			while (cacheSize != 0)
			{
				cache.push_back(Line(blockSize));
				cacheSize -= blockSize;
			}
		}

		struct Address
		{
			int BlockNum;
			int LineNum;
			int Tag;
			int Offset;
			int FullAddress;

			Address(int address)
			{
				FullAddress = address;
				BlockNum = address / offsetMax;
				LineNum = BlockNum / tagMax;
				Tag = BlockNum / (LineNum + 1);
				Offset = address - BlockNum * offsetMax;

				cout << "\nLine: " << LineNum << "\tTag: " << Tag << endl;
			};
		};

		void AccessCache(int address, int signal = 0, int value = 0)
		{
			Address adrs = Address(address);
			Line& line = cache[adrs.LineNum];
			if (line.Tag == adrs.Tag)
			{
				cout << "Cache Hit\n";
			}
			else
			{
				cout << "Cache Miss\n";

				int blockStart = adrs.FullAddress - adrs.Offset;
				for (int i = 0; i < offsetMax; ++i)
				{
					line.Block[i] = disc[blockStart + i];
				}
				line.Tag = adrs.Tag;
			}

			if (signal == 1) { line.Block[adrs.Offset] = value; }
		}

		void PrintCacheBlock(int LineNum)
		{
			if (cache[LineNum].Tag == -1)
			{
				cout << "Block not allocated in cache\n";
				return;
			}

			cout << "Word\tValue\n";
			for (int i = 0; i < cache[LineNum].Block.size(); ++i)
			{
				cout << i << '\t' << cache[LineNum].Block[i] << endl;
			}
		}

	private:
		static int tagMax, lineMax, offsetMax;
		vector<int> disc;
		vector<Line> cache;
};
int Memory::tagMax = 0;
int Memory::lineMax = 0;
int Memory::offsetMax = 0;

unique_ptr<Memory> EnterParams(void)
{
	int memSize, cacheSize, blockSize;
	cout << "Enter main memory size (in words): ";
	cin >> memSize;
	cout << "Enter cache size (in words): ";
	cin >> cacheSize;
	cout << "Enter block size (in words per block): ";
	cin >> blockSize;

	return make_unique<Memory>(memSize, cacheSize, blockSize);
}

int Menu(void)
{
	cout << "\n1) Enter Parameters\n";
	cout << "2) Access cache for reading/writing and transfer data\n";
	cout << "3) Display the contents of a single block of the cache\n";
	cout << "4) Quit Program\n\n";
	cout << "Enter Selection: ";

	int value;
	cin >> value;
	return value;
}

int main(void)
{
	bool exit = false;
	unique_ptr<Memory> mem = nullptr;

	while (!exit)
	{
		switch (Menu())
		{
			case 1: mem = EnterParams();
				break;

			case 2: if (mem == nullptr) { break; }
				int address, signal, value;
				cout << "Enter 0 for read or 1 for write: ";
				cin >> signal;
				cout << "Enter address to access: ";
				cin >> address;
				if (signal == 1)
				{
					cout << "Enter value to write: ";
					cin >> value;
				}
				mem->AccessCache(address, signal, value);
				break;

			case 3: if (mem == nullptr) { break; }
				int block;
				cout << "Enter block of cache to print: ";
				cin >> block;
				mem->PrintCacheBlock(block);
				break;

			case 4: exit = true;
				break;

			default: cerr << "Bad Input\n";
				 break;
		}
	}
	return 0;
}
