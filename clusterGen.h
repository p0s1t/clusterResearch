#ifndef CLUSTER_GEN_H
#define CLUSTER_GEN_H

class ClusterGen{

public:

ClusterGen(){};

~ClusterGen(){};

private:

typedef struct Cluster(){

double center;

vector<vector<double> > dimensions;

vector<double> centers;//midpoints of respective dimensions; used to build the rest of the cluster; makes calculating buffer easier 

double maxD;
double minD;
double density;

double minG;
double maxG;
double gradient;

double minV;
double maxV;
double variance;

int minDims;
int maxDims;
int nDims;

int maxB;
int minB;
int buffer;

int minN;
int maxN;
int N;

bool uniformB;//buffer
bool uniformG;//gradient
bool uniformV;//variance (noise)
bool uniformN;//number of data values in cluster
bool uniformD;//density
bool uniformDim;//dimensions

Cluster prev;//the one before this one (ordered by index)
Cluster next;//the one after (again, ordered by index)

}//end Cluster efstruct def



};

#endif
