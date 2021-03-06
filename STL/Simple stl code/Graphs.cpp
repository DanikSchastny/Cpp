// Граф задан набором вершин и ориентированных дуг. Найти вершины, в которые не входит ни одина дуга
//

#include "stdafx.h"

#include <numeric>
#include <iomanip>
#include <complex>
#include <float.h>
#include <cfloat>

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

//#include <cstring>
#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <ostream>
#include <algorithm>

#pragma hdrstop

struct Node
{
	int NodeStart,
		NodeFinish;

	friend std::istream& operator >> (std::istream& input, Node& vertexes)
	{
		input >> vertexes.NodeStart >> vertexes.NodeFinish;
		return input;
	}
};


//=======================================================================================================================================================//
int main()
{
	std::vector<Node> vEdges;
	std::set<int> fedges;

	std::cout << "Enter the arcs of grapph. To stop, enter the letter:" << std::endl;
	std::copy(std::istream_iterator<Node>(std::cin), std::istream_iterator<Node>(), std::back_inserter(vEdges));

	std::for_each(vEdges.begin(), vEdges.end(), [&fedges](Node x) { fedges.emplace(x.NodeStart); });
	std::for_each(vEdges.begin(), vEdges.end(), [&fedges](Node x) { if (fedges.count(x.NodeFinish) > 0){fedges.erase(x.NodeFinish);}});

	std::cout << "Points in which doesn't enter any of arcs" << std::endl;
	std::copy(fedges.begin(), fedges.end(), std::ostream_iterator<int>(std::cout,"  "));

	system("pause");
    return 0;
}

