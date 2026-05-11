#include <iostream>
#include <vector>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s1) ;

int main(){
    int count = 0;


    cout << "Number of distinct words : " << count << endl;
    cout << "\nThe top 20 most popular words: \n";
    // ...
    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4725

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */