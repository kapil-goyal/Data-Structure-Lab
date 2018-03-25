#include <iostream>
using namespace std;

//This function will calculate hash value of string for a given length
unsigned int hash_val(string str, unsigned int base, unsigned int prime, unsigned int len) {
	unsigned int result = 0;
	for (unsigned int i = 0; i < len; ++i) {
		result = (base*result + str[i])%prime;
	}
	return result;
}

int main()
{
	unsigned int base = 11, prime = 15487469; //Base and Prime

	unsigned int T;							//No. of test cases
	cin >> T;
	while(T--)
	{
		string source;
		string pat;

		cin >> source >> pat;	//input of source string and pattern string

		unsigned int lenpat = pat.length(),chk=1; //check is used for termination and will become 0 when it reaches the end of string
		unsigned int h = 1;						 //h is a utility value
		for (unsigned int _ = 0; _ < lenpat-1; ++_) {
			h = ((base)*h)%prime;
		}
		while(source.length() >= lenpat && chk ) {

			unsigned int start_i=0;	
			unsigned int lensor = source.length();
			unsigned int hash_val1 = hash_val(source,base,prime,lenpat); //hash value of ist substring
			unsigned int hash_val2 = hash_val(pat,base,prime,lenpat);	//hash value of pattern given

			while(chk) {

				if(hash_val1 == hash_val2) {	//if two string have same hash value 
					if(source.compare(start_i,lenpat,pat,0,lenpat) == 0) {	//then compare strings characterwise
						source.erase(start_i,lenpat);	//then delete that part from source string
						break;
					}
				}

				if(start_i + lenpat == lensor ) {	//if we have reached the end then stop and make chk 0
					chk=0;
					break;
				}

				hash_val1 = (base*(hash_val1 - (h*source[start_i])%prime + prime) + source[start_i+lenpat])%prime; //move substring by one char
				start_i++;
			}			
		}
		cout << source << endl; //print final source string remaining
	}
	return 0;
}