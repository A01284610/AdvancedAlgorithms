#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

using namespace std;




int LCS(string S1, string S2) {
    unsigned char LCS[250][250];
    

    int n = S1.length();
    int m = S2.length();
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (S1[i] == S2[0]) {
            LCS[i][0] = 1;
            max = 1;
        }
        else {
            LCS[i][0] = 0;
        }

    }
    for (int j = 0; j < m; j++) {
        if (S1[0] == S2[j]) {
            LCS[0][j] = 1;
            max = 1;
        }
        else {
            LCS[0][j] = 0;

        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (S1[i] == S2[j]) {
                LCS[i][j] = LCS[i - 1][j- 1] + 1;
            if (LCS[i][j] > max)
                max = LCS[i][j];
            }
            else {
                LCS[i][j] = 0;
            }
        }
    }
}


int main(){

    string S1="xblzkhoshddyliqcelivudakdnsmuharmxjplmrlouvcdfapugfngmasmssovggtchoedrfqzegolnjqagtyuohtrgkacomzxxoghnitmjbgyqyyqsmpsnyrkoxawnxrecatxabqnveqxynwhsgenuqgtsgmohkwntftusxlndwodspetapoezdekuwzfpkmcnqeimuzfarpizugcupjbewsdpagznlxjdfoickyqtwzebyupayoxhgmaw";
    string S2="srrrfkzhbbzaokoorahkqwdjxqhhfxbyfhqooftnbjcwwprdnknwawycoarjtyvjxqjnduegwafmxsjaxifccqehnphzidrerwyupakhyhchwoklyarqgnmfmaorpmokpqyejqwbbvjhtlfxgedqzchoimqvctxdyjdoijwnhtnqyjlhqhnmxhacjfgolwmdnuqnbdcwwopkeechipdolwlgucakwaskeangjwzhmsgzdpcxuflmgjwlay";

    cout << LCS(S1,S2);

  return 0;
}