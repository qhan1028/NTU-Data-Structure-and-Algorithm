#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <vector>

int tree_predict(double *attr);

using namespace std;

using std::string;

#define MAX_FEATURE (1024+1)

int main(int argc,char** argv) {
  int correct = 0;
  int total = 0;
  
  double* features = new double[MAX_FEATURE];

  std::ifstream fin;
  string istring;
  fin.open(argv[1]);

  while (std::getline(fin, istring)) {
    total++;
    char *cstring, *tmp;
    int label;
    memset(features, 0, sizeof(double) * MAX_FEATURE);

    cstring = new char[istring.size() + 1];
    strncpy(cstring, istring.c_str(), istring.size()+1);

    tmp =  strtok(cstring, ": ");
    label = atoi(tmp);
    tmp = strtok(NULL, ": ");

    while(tmp != NULL) {
      int id = atoi(tmp);
      tmp = strtok(NULL, ": ");
      features[id] = atof(tmp);
      tmp = strtok(NULL, ": ");
    }

    delete[] cstring;

    int prediction = tree_predict(features);
    if (prediction == label) correct++;
  }
  printf("Accuracy: %d/%d = %lf%%\n", correct, total, correct*100.0/total);
  delete[] features;
}
