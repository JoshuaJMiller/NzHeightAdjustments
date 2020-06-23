/*--------------------------------------------------------------

TWO SOLUTIONS TO THE PROBLEM NEED TO BE WRITTEN:
	- perfect world "magic" adjustment to *height* neighbor
	- real world adjustment to actual index neighbor
	
--------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void printVecDouble(const std::vector<double> p_vec);
std::pair<double, double> getMaxMin(const std::vector<double> &p_nzHeights);
double getRange(const std::vector<double> &p_vec);

//used for determining outliers
std::pair<double, double> getHighLow(std::vector<double> p_sortedNzHeights)
{
	double Q1{};
	double Q2{};
	double Q3{};
	double IQR{};
	double high{};
	double low{};
	int middle{};
	double mean{};
	double size = static_cast<double>(p_sortedNzHeights.size());

	std::sort(p_sortedNzHeights.begin(), p_sortedNzHeights.end());
	printVecDouble(p_sortedNzHeights);

	if ((std::fmod(size / 2, 1.0) == 0.5))
	{
		//odd number of elements
		std::cout << "ODD NUM OF ELEMENTS" << std::endl;
		Q2 = p_sortedNzHeights.at((size / 2));
		std::cout << "Q2 = " << Q2 << std::endl;
		middle = (size / 2);
		std::cout << "Middle = " << middle << std::endl;
		size = middle;
		if ((std::fmod(size / 2, 1.0) == 0.5))
		{
			//odd number in lower and upper half
			std::cout << "ODD NUM BELOW AND ABOVE Q2" << std::endl;
			Q1 = p_sortedNzHeights.at((middle / 2));
			std::cout << "Q1 = " << Q1 << std::endl;
			Q3 = p_sortedNzHeights.at(middle + (middle / 2) + 1);
			std::cout << "Q3 = " << Q3 << std::endl;
		}
		else if ((std::fmod(size / 2, 1.0) == 0))
		{
			//even number in lower and upper half
		}
	}
	else if ((std::fmod(size / 2, 1.0) == 0))
	{
		//even number of elements
		mean = (p_sortedNzHeights.at(p_sortedNzHeights.size() / 2) + p_sortedNzHeights.at((p_sortedNzHeights.size() / 2) - 1)) / 2;
		Q2 = mean;
		std::cout << "Q2 = " << Q2 << std::endl;
	}
	
	IQR = Q3 - Q1;
	std::cout << "IQR = " << IQR << std::endl;

	high = Q3 + (1.5 * IQR);
	low = Q1 - (1.5 * IQR);

	std::pair<double, double> p1{ high, low };
	return p1;
}

void printVecDouble(const std::vector<double> p_vec)
{
	std::cout << "[ ";
	for (size_t i{ 0 }; i < p_vec.size() - 1; ++i)
	{
		std::cout << p_vec.at(i) << ", ";
	}
	std::cout << p_vec.at(p_vec.size() - 1) << " ]" << std::endl;
}

//used for printing high low determined by getHighLow (outliers)
void printHighLow(const std::pair<double, double> p_highLow)
{
	std::cout << "High = " << p_highLow.first << std::endl;
	std::cout << "Low = " << p_highLow.second << std::endl;
	
}

double getRange(const std::vector<double> &p_nzHeights)
{
	std::pair<double, double> maxMin = getMaxMin(p_nzHeights);
	return maxMin.first - maxMin.second;
} 

int nzlsOutFromLower(double p_range, std::vector<double> p_nzlHeights)
{
	int counter{0};
	
	std::sort(p_nzlHeights.begin(), p_nzlHeights.end());
	for (size_t i{ 1 }; i < p_nzlHeights.size(); ++i)
	{
		if ((p_nzlHeights.at(i) - p_nzlHeights.at(0)) > p_range)
		{
			++counter;
		}
	}

	return counter;
}

int nzlsOutFromUpper(double p_range, std::vector<double> p_nzlHeights)
{
	int counter{0};

	std::sort(p_nzlHeights.begin(), p_nzlHeights.end());
	for (size_t i{ 0 }; i < (p_nzlHeights.size() - 1); ++i)
	{
		if ((p_nzlHeights.at((p_nzlHeights.size() - 1)) - p_nzlHeights.at(i)) > p_range)
		{
			++counter;
		}
	}

	return counter;
}

std::pair<double, double> getMaxMin(const std::vector<double> &p_nzHeights)
{
	std::pair<double, double> maxMin{p_nzHeights.at(0), p_nzHeights.at(0)};
	for (size_t i{ 1 }; i < p_nzHeights.size(); ++i)
	{
		if (p_nzHeights.at(i) < maxMin.second)
		{
			maxMin.second = p_nzHeights.at(i);
		}
		else if (p_nzHeights.at(i) > maxMin.first)
		{
			maxMin.first = p_nzHeights.at(i);
		}
	}
	return maxMin;
}

double getMidPoint(const std::vector<double> &p_nzHeights)
{
	std::pair<double, double> maxMin = getMaxMin(p_nzHeights);
	double range = getRange(p_nzHeights);
	double mid = maxMin.second + (range / 2);
	return mid;
}

void makeMove(double p_position, double p_a, double p_b, double p_c)
{
	std::cout << "moved to " << p_position << " at " << p_a << ", " << p_b << ", " << p_c << std::endl;
}

void settle()
{
	std::cout << "settled" << std::endl;
}

void moveToCoord(std::pair<double, double> p_coor, std::vector<double> p_params)
{
	double x = p_coor.first;
	double y = p_coor.second;

	makeMove(x, p_params.at(0), p_params.at(1), p_params.at(2));
	makeMove(y, p_params.at(0), p_params.at(1), p_params.at(2));
	settle();
	settle();
}

std::pair<int, int> getMaxMinIndex(const std::vector<double> &p_nzHeights)
{
	std::pair<double, double> maxMin{ p_nzHeights.at(0), p_nzHeights.at(0) };
	std::pair<int, int> maxMinIndex{ 0, 0 };
	for (size_t i{ 1 }; i < p_nzHeights.size(); ++i)
	{
		if (p_nzHeights.at(i) < maxMin.second)
		{
			maxMin.second = p_nzHeights.at(i);
			maxMinIndex.second = i;
		}
		else if (p_nzHeights.at(i) > maxMin.first)
		{
			maxMin.first = p_nzHeights.at(i);
			maxMinIndex.first = i;
		}
	}
	return maxMinIndex;
}



std::vector<int> getOutOfSpecIndices(double p_rangeSpec, std::vector<double> p_nzHeights)
{
	double range = getRange(p_nzHeights);
	std::pair<double, double> maxMin = getMaxMin(p_nzHeights);

	std::pair<int, int> maxMinIndices = getMaxMinIndex(p_nzHeights);

	std::vector<double> tempHeights = p_nzHeights;
	double tempRange = range;

	std::vector<int> outOfSpecIndices;

	if (range > p_rangeSpec)
	{
		//erase min from tempHeights
		tempHeights.erase(tempHeights.begin() + maxMinIndices.second);
		
		//print tempHeights (debug)
		std::cout << "Removing min from vector . . . \n\n";
		printVecDouble(tempHeights);

		tempRange = getRange(tempHeights);
		std::cout << "\nnew range: " << tempRange << std::endl << std::endl;
		
		if (tempRange < p_rangeSpec)
		{
			std::cout << "CASE 1:" << std::endl;
			outOfSpecIndices.push_back(maxMinIndices.second);
			return outOfSpecIndices;
		}
		else if (tempRange > p_rangeSpec)
		{
			//fill temp vec back up
			tempHeights = p_nzHeights;
			
			//print tempheights (debug)
			std::cout << "\nReplacing removed element . . . \n\n";
			printVecDouble(tempHeights);

			//remove max
			tempHeights.erase(tempHeights.begin() + maxMinIndices.first);
			
			//print tempheights (debug)
			std::cout << "Removing max from vector . . . \n\n";
			printVecDouble(tempHeights);

			tempRange = getRange(tempHeights);
			std::cout << "\nnew range: " << tempRange << std::endl << std::endl;

			if (tempRange < p_rangeSpec)
			{
				std::cout << "CASE 2:" << std::endl;
				outOfSpecIndices.push_back(maxMinIndices.first);
				return outOfSpecIndices;
			}
			else if (tempRange > p_rangeSpec)
			{
				//fill temp vec back up
				tempHeights = p_nzHeights;
				
				//print tempheights (debug)
				std::cout << "\nReplacing removed element . . . \n\n";
				printVecDouble(tempHeights);

				//remove both min and max, check range
				tempHeights.erase(tempHeights.begin() + maxMinIndices.first);
				maxMinIndices = getMaxMinIndex(tempHeights);
				tempHeights.erase(tempHeights.begin() + maxMinIndices.second);

				//reset maxMinIndices
				maxMinIndices = getMaxMinIndex(p_nzHeights);

				//print tempheights (debug)
				std::cout << "Removing max and min from vector . . . \n\n";
				printVecDouble(tempHeights);

				tempRange = getRange(tempHeights);
				std::cout << "\nnew range: " << tempRange << std::endl << std::endl;
				if (tempRange < p_rangeSpec)
				{
					std::cout << "CASE 3:" << std::endl;
					outOfSpecIndices.push_back(maxMinIndices.first);
					outOfSpecIndices.push_back(maxMinIndices.second);
					return outOfSpecIndices;
				}
				else if (tempRange > p_rangeSpec)
				{
					std::cout << "CASE 4:\nprocess must be repeated." << std::endl;
				}
			}
		}
	}

	//while (tempRange > p_rangeSpec)
	{

		//fill tempHeights with all indexes of p_nzHeights except min
		//check range of tempHeights

		//if temp range is in spec calculate how far away min is from second lowest

		//do the same with max

		//which is further away?

	}
	
	return outOfSpecIndices;
}

void printNzToAdjust(std::vector<int> p_vec)
{
	std::cout << "Nozzle(s) to adjust: [ ";
	if (p_vec.size() == 1)
	{
		std::cout << p_vec.at(0) << " ]" << std::endl;
	}
	else if (p_vec.size() > 1)
	{
		for (size_t i{ 0 }; i < p_vec.size() - 1; ++i)
		{
			std::cout << p_vec.at(i) << ", ";
		}
		std::cout << p_vec.at(p_vec.size() - 1) << " ]" << std::endl;
	}
	else if (p_vec.size() == 0)
	{
		std::cout << "N/A" << " ]" << std::endl;
	}
}

int main()
{
/*
	MENTAL PROCESS 1:
	step 1: check max - min < spec
	step 2: scan for obvious outliers
	step 3: remove obvious outliers or suspect outliers
	step 4: is newly reduced data set average within spec?
	step 5: if so, put outlier back in data set, set outliers to neighbors height
		- determining which neighbor relies on whether or not in-spec-neighbor is present
		- if all neighbors are out of spec, choose set neighbor to it's neighbor, then set to neighbors down the line
	step 6: if not... repeat?

	IMPROVEMENT(?) TO MENAL PROCESS 1:
	step 1: identify min and max
	step 2: identify how many nozzles are out of spec in comparison to min
	step 3: identify how many nozzles are out of spec in comparison to max
	step 4: does it require less moves to move out of spec nozzles down to meet min, or up to meet max?
	step 5: do less. use neighbors
	
	*/

	double rangeSpec{ 10.0 };

	//CASE 1: removing min brings vec in spec
	
	std::vector<double> nzHeights1{ 100, 101, 103, 104, 80, 106 };
	printVecDouble(nzHeights1);

	std::vector<int> nozzlesToAdjust = getOutOfSpecIndices(rangeSpec, nzHeights1);
	printNzToAdjust(nozzlesToAdjust);

	//CASE 2: removing max brings vec in spec

	std::vector<double> nzHeights2{ 100, 120, 103, 104, 105, 106 };
	printVecDouble(nzHeights2);

	nozzlesToAdjust = getOutOfSpecIndices(rangeSpec, nzHeights2);
	printNzToAdjust(nozzlesToAdjust);

	//CASE 3: removing min AND max brings vec in spec

	std::vector<double> nzHeights3{ 100, 120, 103, 104, 80, 106 };
	printVecDouble(nzHeights3);

	nozzlesToAdjust = getOutOfSpecIndices(rangeSpec, nzHeights3);
	printNzToAdjust(nozzlesToAdjust);

	//CASE 4: removing min AND max does NOT bring vec in spec - need to write what to do in this case - in real life if the final two nozzles were out of spec: "Nozzle heights not within adjustable spec. Coarse bench alignment needed." 

	std::vector<double> nzHeights4{ 119, 120, 103, 104, 80, 106 };
	printVecDouble(nzHeights4);

	nozzlesToAdjust = getOutOfSpecIndices(rangeSpec, nzHeights4);
	printNzToAdjust(nozzlesToAdjust);

	/*double midPoint = getMidPoint(nzHeights);
	std::cout << "Mid point: " << midPoint << std::endl;

	std::cout << "Nozzles to move down: " << nzlsOutFromLower(10, nzHeights) << std::endl;
	std::cout << "Nozzles to move up: " << nzlsOutFromUpper(10, nzHeights) << std::endl;*/


	/*double paramA{ 10 };
	double paramB{ 20 };
	double paramC{ 30 };

	double xPos{ 12.2 };
	double yPos{ 20.4 };

	moveToCoord({ xPos, yPos }, { paramA, paramB, paramC });*/

	return 0;
}