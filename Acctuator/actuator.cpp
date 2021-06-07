#include "acctuator.h"

Acctuator::Acctuator(int S, int E, int num){
    startReed = S;
    endRedd = E;
    accNum = num;
}

Acctuator::execute(){
    if(startReed != 0){
        std::cout << "Solenoid Acctuate";
    } else if(endRedd != 0){
        std::cout << "Solenoid Acctuate";
    }
}