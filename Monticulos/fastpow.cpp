#include <iostream>

using namespace std;

int fastpow(int base, int n){
    if(n == 0){
        return 1;
    }
    if(n == 1){
        return base;
    }
    if(n % 2 == 0){
        int mitad = fastpow(base, n/2);
        return mitad * mitad;
    } else {
        return base * fastpow(base, n-1);
    }
}

int main(){
    cout << fastpow(2, 5) << endl;
    return 0;
}