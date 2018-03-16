#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

using namespace std;

map<size_t, vector<size_t>> formatTxt(char* LLVMOutput);

int main(int argc, char* argv[])
{

}

map<size_t, vector<size_t>> formatTxt(char* LLVMOutput)
{
	hash<string> hash_fn;
	map<size_t, vector<size_t>> retValue;
	stringstream ss(LLVMOutput);
	string line;
	pair<size_t, vector<size_t>> scope;

	if (LLVMOutput != NULL)
	{
		while (getline(ss,line,'\n'))
		{
			if (line.find("SCOPE") != string::npos)
			{
				if (scope.first != 0)
				{
					retValue.insert(scope);
					scope.first = 0;
					scope.second = vector<size_t>();
				}
				scope.first = hash_fn(line.substr(line.find(":") + 1));
			}
			if (line.find("FUNCTION") != string::npos)
			{
				scope.second.push_back(hash_fn(line.substr(line.find(":") + 1)));
			}
		}
	}

	return retValue;
}