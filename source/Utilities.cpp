#include "Utilities.h"

vector<wstring> readWstringListFromFile(string path)
{
	wifstream inputFile(path);

	if (!inputFile.is_open())
		throw Exception("File \"" + path + "\" not found");
	
	wstring str;
	vector<wstring> list;
	while (std::getline(inputFile, str)) 
		list.push_back(str);

	inputFile.close();
	return list;
}

double binomial_coefficient(unsigned int n, unsigned int k)
{
	static map<pair<unsigned int, unsigned int>, double> binomial_coefficients_map;

	if (k > n)
		return 0;

	if (n == 0 || n == k)
		return 1;

	if (!binomial_coefficients_map.count({ n, k }))
		binomial_coefficients_map[{ n, k }] = binomial_coefficient(n - 1, k - 1) + binomial_coefficient(n - 1, k);
	
	//cout << binomial_coefficients_map[{n, k}] << endl;
	return binomial_coefficients_map[{n, k}];
}

void writeWstringListToFile(string path, vector<wstring> list)
{
	wofstream outputFile(path);

	if (!outputFile.is_open())
		throw Exception("Couldn't open " + path);

	for (wstring line : list)
		outputFile << line << endl;

	outputFile.close();
}

vector<string> readStringListFromFile(string path)
{
	ifstream inputFile(path);

	if (!inputFile.is_open())
		throw Exception("file \"" + path + "\" not found");

	string str;
	vector<string> list;
	while (std::getline(inputFile, str))
		list.push_back(str);

	inputFile.close();
	return list;
}

void enterToExit()
{
	cout << "Press enter to exit" << endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//cin.get();
}

wstring reverseHebrew(wstring str) 
{
	wstring::iterator startEng;
	for (wstring::iterator it = str.begin(); it < str.end(); ++it)
	{
		if (isHebrew(*it))
		{
			startEng = it;
			while (it < str.end() && (isHebrew(*it) || iswspace(*it)))
				++it;

			std::reverse(startEng, it);
			if (it == str.end())
				break;
		}
	}

	return str;
}

bool isHebrew(wchar_t ch)
{
	return 0x0590 <= ch && ch <= 0x05FF;
}

vector<bool> stringToBoolVector(string str)
{
	vector<bool> list;
	for (char c : str)
	{
		if (isBool(c))
			list.push_back(c == '1');
		else
			throw Exception("String contains a non-bool character");
	}
	return list;
}

template <class T>
vector<T> copySubVector(const vector<T>& vec, int start, int end)
{
	vector<T> subVec;
	for (int i = start; i <= end; ++i)
		subVec.push_back(vec[i]);

	return subVec;
}

bool readBool()
{
	return _getch() == '1';
}

bool isBool(char c)
{
	return c == '0' || c == '1';
}

long long nowTimeMs()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}