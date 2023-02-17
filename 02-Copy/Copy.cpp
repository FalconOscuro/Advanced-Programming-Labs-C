#include <iostream>
#include <fstream>
using namespace std;

/*
* Partially completed program
* The program should copy a text file
*
*/

bool Copy(char filenamein[], char filenameout[])
{
	// ----- Read -----
	ifstream inFile(filenamein);
	if (!inFile)
		return false;
	
	// Finds file size by seeking until the end of file is found
	unsigned long int fileLen = 0;
	for (; inFile.peek() != EOF; inFile.seekg(++fileLen));

	// Allocate appropriately size buffer for file size
	char* fileBuf = new char[fileLen + 1];
	if (!fileBuf)
		return false;

	// Copy into buffer
	inFile.seekg(0);
	const bool rFail = !inFile.read(fileBuf, fileLen);

	// Close and check copy success
	inFile.close();
	if (rFail)
		return false;


	// ----- Write -----
	ofstream outFile(filenameout);
	if (!outFile)
		return false;

	// Copy buffer into file
	const bool wFail = !outFile.write(fileBuf, fileLen);

	// Close and ensure success
	outFile.close();
	if (wFail)
		return false;

	return true;
}

int main(int argn, char* argv[])
{
	if (argn != 3) {
		cerr << "Usage: " << argv[0] << " <input filename> <output filename>" << endl;
		int keypress; cin >> keypress;
		return -1;
	}

	if (Copy(argv[1], argv[2]))
	{
		cout << "Copy successful" << endl;
	}
	else
	{
		cout << "Copy error" << endl;
	}
}