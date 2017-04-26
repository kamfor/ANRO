#include <iostream>
#include <kdl/kdl.hpp>
#include <kdl/tree.hpp>
#include <kdl/chain.hpp>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main(int argc,char *argv[])
{
	KDL::Chain chain;
	
	// Deklaracje zmiennych i stałych
	double const PI = M_PI;
	double d1, d2, d3;
	if(argc == 4) {
		d1 = strtol(argv[1], NULL, 10);
		d2 = strtol(argv[2], NULL, 10);
		d3 = strtol(argv[3], NULL, 10);
	}
	else {
		d1 = 2;
		d2 = 2;
		d3 = 2;
	}

	double zlacze[3], koncowka[3];
	double roll, pitch, yaw; // Szukane parametry

	// Dodanie segmentów - węzłów
	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ),KDL::Frame::DH(0, 0, d1, 0)));
	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotY),KDL::Frame::DH(0, PI/2, d2, PI/2)));
	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotX),KDL::Frame::DH(0, PI/2, d3, PI/2)));
	
	
	for (int i = 0; i < 3; i++)
	{
			for(int j = 0; j < 3; j++)
			{
				zlacze[j] = chain.getSegment(i).getFrameToTip().p.data[j]; // Zwraca pozycję końcówki segmentu nadrzędnego
			}

		chain.getSegment(i).getFrameToTip().M.GetRPY(roll, pitch, yaw);
	
	cout << "Zlacze " << i << " xyz : " << zlacze[0] << ", " <<zlacze[1] << ", " << zlacze[2] << endl;		
	cout << "Zlacze " << i << " rpy : " << roll << ", " << pitch << ", " << yaw << endl;
	}

	return 0;
}
