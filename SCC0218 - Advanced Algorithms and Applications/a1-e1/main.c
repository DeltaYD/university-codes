#include <stdio.h>
#include <stdlib.h>
#include "stableMatchingFile.h"

int main(void){

    int **mPref, **fPref;
    int it = 0, matches = 0;

    //  How many iterations
    scanf("%d", &it);
    for(int count = 0; count < it; count++){

        //  Start by making lists of preference
        scanf("%d", &matches);
        fPref = makePreferenceList(matches);
        mPref = makePreferenceList(matches);

        //  Now that they are done, match them together
        matchingAlgorithm(mPref, fPref, matches);

        //  Show the matches
        printMatches(mPref, fPref, matches);

        //  Finally, free up some space
        destroyPref(fPref, matches);
        destroyPref(mPref, matches);

        //  Repeat if it > 1
    }


    //  The end
    return 0;
}