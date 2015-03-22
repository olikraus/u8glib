
#include "bitmap.h"
#include <iostream>

int main(int argc, const char *argv[])
{
	if (argc < 4) {
		printf("Usage: %s <infile> <outheader> <arrayname>\n", argv[0]);
	}

 	CBitmap cm(argv[1]);

	unsigned w = cm.GetWidth(), h = cm.GetHeight(), b = cm.GetBitCount();

	std::cout << "Read bm " << argv[1] << " width " << w << " height " << h << " bm " << b << std::endl;

	cm.SaveBM8IncludeHex(argv[2], argv[3]);

	return 0;
}
