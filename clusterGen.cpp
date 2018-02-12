
#include 'clusterGen.h'

#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <iterator>



using namespace std;

clusterGen::clusterGen(){};

~clusterGen::clusterGen(){};

vector<Cluster> clusterGen::makeClusters(int minC, int maxC, int C, int minDim, int maxDim, int Dim, int minN, int maxN, int N, int minB, int maxB, int B, double minInitVal, double maxInitVal, double initVal, double minD, double maxD, double D, double minV, double maxV, double V, bool hasNoise, double minG, double maxG, double G){

	
	vector<Cluster> vec;//container for the testing clusters that will be run to determine program viability

	bool uniformDensity = false;
	bool uniformN = false;
	bool uniformNoise = false;
	bool uniformGrade = false;
	bool uniformBuffer = false; 
	bool uniformInitVal = false;
	bool hasVariation = false;
	
	Cluster c = {};
	Cluster cNext = {};
	
	int nClusters;
	int nDims;
	int nValues;
	int buffer;

	double value;

	double gradient;
	double density;
	double variance;

	if(C == NULL) nClusters = getRanInt(minC, maxC);
	else nClusters = C;

	if(Dim == NULL) nDims = getRanInt(minDim, maxDim);
	else nDims = Dim;

	if(N == NULL) nValues = getRanInt(minN, maxN);
	else nValues = N;

	if(B == NULL) buffer = getRanInt(minB, maxB);
	else buffer = B;

	if(G == NULL) gradient = getRanDub(minG, maxG);
	else gradient = G;

	if(D == NULL) density = getRanDub(minD, maxD);
	else density = D;

	if(V == NULL) variance = getRanDub(minV, maxV);
	else variance = V;

	if(InitVal == NULL) value = getRanDub(minInitVal, maxInitVal);
	else value = InitVal;


	vector<double> dimension;


	for(int i = 0; i < nClusters; i++){

	//binary decision 2 determine uniformity of potentially stochastic metrics involved in cluster building

	int randomDensity = getRanInt(1,2);
	if((randomDensity % 2) == 0) uniformDensity = true;//is the density gradient relevant?

	int randomNoise = getRanInt(1,2);
	if((randomNoise % 2) == 0) uniformNoise = true;//is there uniformity in the noise?

	int randomGrade = getRanInt(1,2);
	if((randomGrade % 2) == 0) uniformGrade = true;//if density is non-uniform, does the gradient vary?

	int randomN = getRanInt(1,2);
	if((randomN % 2) == 0) uniformN = true;//does every dimension have the same number of values?

	int randomBuffer = getRanInt(1,2);
	if((randomBuffer % 2) == 0) uniformBuffer = true;//is the separation between the cluster centers uniform? If not, each dimension will have a different buffer based on buffer boundaries from user 

	int randomValue = getRanInt(1,2);
	if((randomValue % 2) == 0) uniformInitValue = true;//does every dimension start with the same center point?

	int randomVariation = getRanInt(1,2);
	if((randomVariation % 2) == 0) hasVariation = true;//whether or not to include noise in the data 

		if(i > 1) {//linked list of clusters for reference while buffering the data values 
			   //note: buffer is not exactly an overlay due to stochastic declaration of value, but inital point *is* the exact buffered value
			   //and all derivatives of that value are relative to that initial point, so overlay between clusters is preserved without making data values blatantly redundant
	
		c.next = cNext;
		cNext.prev = c;
		c = cNext;
					
		}

		c.index = i;

		c.uniformB = uniformBuffer;

		if(uniformBuffer == false) buffer = getRanInt(minb, maxB);
		
		c.buffer = buffer;
	
		c.uniformD = uniformDensity;//d for density -- change in value from one to the next in consecutive order
		c.uniformV = uniformNoise;//v for variance -- noise
		c.uniformG = uniformGrade;//g for gradient -- change in density
		c.uniformN = uniformN;//n for number of values per dimension

	
		if(uniformD == false) nDims = getRanInt(minDim, maxDim);
		else c.nDims = nDims;

			for(int d = 0; d < nDims; d++){

		
				if(uniformN == false){

				nValues = getRanInt(minN, maxN);//get number of data points in this cluster
							
				c.values.at(nDim).push_back(nValues);
	
				}//end if uniformN 
	
					if(uniformInitValue == false) value = getRanDub(minInitVal, maxInitVal);//pull a value given user-defined boundaries
					

					if(c.uniformV == false){//add noise once value is defined

						 c.noise = variance;
						 value += variance;
						
								}//end if re: uniformity of noise
					else {
						c.maxV = maxV;
						c.minV = minV;

						variance = getRanDub(minV, maxV);

						value += variance;

								}//end else re: uniformity of noise
		
						c.centers.at(d).push_back(value);//add (possibly variated) value to center container for this dimension (d)
					for(int r = 0; i < nValues; r++){


			
					if(c.uniformD == false){//add density+gradient if density uniformity is false
						 c.density = density;

						 value += density;
						
								}//end if re: uniformity of density
					else {
						c.maxD = maxD;
						c.minD = minD;

						density = getRanDub(minD, maxD);

								if(c.uniformG == false){//figure the gradient to add to density

									c.grade = gradient;
									value += density+gradient;
						 
						
											}//end if re: uniformity of grade
								else {

									c.maxG = maxG;
									c.minG = minG;

									gradient = getRanDub(minG, maxG);

									value += density+gradient;

											}//end else re: uniformity of density

					
							 dimension.push_back(value);
							 c.center = (dimension.at(c.N/2+buffer));
					

					}//end for each value in this dimension 

						c.dimensions.push_back(dimension);//add dimension to cluster
						dimension.clear();
			
				}//end for each value in nValues
			cNext.prev = c;
			cPrev.next = c;
			vec.push_back(c);//add cluster struct to main container
		}

	return vec;//give em the goods!

}//end makeClusters

double clusterGen::getRanDub(double min, double max){

	std::random_device fortuna;//oh, fortuna!

   	 std::mt19937 verse( fortuna() );

  	  std::uniform_real_distribution<double> uni(min, max);

	double ranDub = uni(verse);//from the universe comes the randomness....

	return ranDub;

}//end get Random Double

int clusterGen::getRanInt(int min, int max){

	std::random_device fortuna;//oh, fortuna!

   	std::mt19937 verse( fortuna() );

   	std::uniform_real_distribution<int> uni(min, max);

	double ranInt = uni(verse);
	return ranInt;


}//end get Random Integer

void clusterGen::runTests(int nTests){


	

	double noiseFactor = 100;//indicates subdivision of density used for noise calcluation
	
	for(int i = 0; i < nTests; i++){

	int C = getRanInt(1, 100);//number of clusters
	int Dim = getRanInt(1, 100000);//number of dimensions
	int N = getRanInt(1, 10000000);//number of data-point values
	int B = getRanInt(1, N-1);//buffer
	double D = getRanDub(.001, .0000001);//density
	double G = getRanDub(D/(double)100, D/(double)10000);//gradient
	double V = getRanDub(D/(double)10000, D/(double)10000000);//variance
	


	

	//max/min values differ by at least two orders of magnitude, and at most seven orders of magnitude
	double maxVal = getRanDub(1000, .001);
	double minVal = getRanDub(.000001, .000000000001);

	
	double variance = getRanDub(meanDensity/noiseFactor, meanDensity/(noiseFactor*noiseFactor));

	bool uniformity = false;
	int uniformityIndicator = getRanInt(100,0);
	if(uniformityIndicator%2 == 0) uniformity = true;//switch density uniformity randomly for tests


	int buffer = (int)(nValues/(getRanInt(nValues-1, 0))); //buffered overlap in cluster data ranges from proximally absolute at min to zero (no overlap) at max

	vector<Cluster> testClusters = makeClusters(nClusters, nDimensions, nValues, meanDensity, minVal, maxVal, gradient, variance, uniformity, buffer);

	if(toFile(testClusters, "testInput.csv")) return 0;//appends to FILE object after first iteration
	else cout << "System error: Outputting clusters' data to file not succesful" << endl;

	}


}//end runTests

bool clusterGen::toFile(vector<Cluster> v, string pathOut, string delimiter){

	
	
	bool success = false;

	string newline = "\n";

	for(auto i = v.begin(); i != v.end(); i++){//for each Cluster struct, write its testable data to a unique file
						//then write a file that will have expected results from QLIINC for comparison post

		ofstream streamOut(pathOut, ios::app);//creates and/or appends data to file as needed

		if(!streamOut.is_open()) cout << "Error in output, file stream unavailable for data logging" << endl;

		else{

			for(auto d = i.dimensions.begin(); d != i.dimensions.end(); d++){//for each dimension in cluster

				for(auto p = d.begin(); p != d.end(); p++){//for each data (p)oint, write to output file

					std::ostringstream converter;
					converter << p;//convert data from numeric value to string
					string dataAsString = converter.str();
					dataAsString += delimiter;//csv files separated by whatever delimiter the user passes in
					ofstream << dataAsString;

				}//end for each point-value in dimension (p)

					ofstream << newline;//add carriage return at end of current row

			}//end for each dimension in cluster (d)

		}//end for each cluster in nTests (i)

	}//end else
	success = true;
	return success;
}//end toFile

int main(int argv, char** argc){

	if(argv > 1){

		int nTests = atoi(argc[0]);

		runTests(nTests);
	}
	else cout << "System input error: Not enough arguments in command line execution to meet program req's" << endl;



}//end main







int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
