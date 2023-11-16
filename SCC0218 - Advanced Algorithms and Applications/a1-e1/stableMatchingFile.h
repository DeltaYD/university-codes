int **makePreferenceList(int nMatches);
void destroyPref(int **target, int n);
int isPreference(int **matrizPref, int h, int m, int cand, int nMatches);
void matchingAlgorithm(int **mPref, int **fPref, int nMatches);
void printMatches(int **mPref, int **fPref, int nMatches);