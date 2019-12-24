//
//  main.cpp
//  StateUpdate
//
//  Created by adeeb mohammed on 22/12/19.
//  Copyright © 2019 adeeb mohammed. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
/*
    two dimensional array given
 minimum no of iteration to update the vector to update the adjacent matrix state
 m * n matrix
 [0 0 0 0 ]
 [0 1 0 1 ]
 
 */

bool updateStates(std::vector<std::vector<int>> statesVector,
                  std::map<int,int> &stateMap,
                  int &filledItems,
                  int totalItems
                  ){
    // true returns stopping of the condition check
    
    int i = 0;
    int j = 0;
    for(std::vector<std::vector<int>>::iterator it = statesVector.begin();
        it != statesVector.end(); ++it
        ){
        for(std::vector<int>::iterator it_1 = it->begin(); it_1 != it->end(); ++it_1){
            // one error case when non zero value enters in the array
            if((*it_1 > 1) || (*it_1 < 0)){
                return true;
            }
            // check for previous state and current state
            // if  previous value is  1 dont update the count and update the array
            if((stateMap[i+j] == 0) && (*it_1 == 1)){
                filledItems++;
            }
            // store the value in the map
            stateMap[i+j] = *it_1;
            j++;
        }
        i++;
    }
    // if all elements are filled with  1 we have to exit
    // if none of the element is 1 then it will goto infinite loop so in that case
    // also we have to return true
    if((filledItems == totalItems) || (filledItems == 0)){
        return true;
    }
    return false;
}

int findMinIteration(std::vector<std::vector<int>> statesVector,
                     int m , int n){
    int iterNum     = 0;
    int totalItems  = m * n;
    int filledItems = 0;
    
    std::map<int,int> stateMap;
    // check whther the all elements are filled initially
    bool result = updateStates(statesVector, stateMap, filledItems, totalItems);
    if(result == true){
        stateMap.clear();
        statesVector.clear();
        return iterNum;
    }
    // when all elements in the vector is processed we can return back
    while(filledItems < totalItems){
        for(signed int i = 0;i < m; i++){
            for(signed int j = 0; j < n ; j++){
                // check whether the server state is previously updated
                if(stateMap[i+j] == 1){
                    // update the left side
                    if((j-1) >= 0){
                        statesVector[i][j-1] = 1;
                    }
                    // update the right side
                    if((j+1) < n){
                        statesVector[i][j+1] = 1;
                    }
                    // update the top side
                    if((i-1) >= 0){
                        statesVector[i-1][j] = 1;
                    }
                    // update the bottom vector
                    if((i+1) < m){
                        statesVector[i+1][j] = 1;
                    }
                }
            }
        }
        iterNum++;
        result = updateStates(statesVector, stateMap, filledItems, totalItems);
        if(result == true){
            break;
        }
    }
    stateMap.clear();
    statesVector.clear();
    return iterNum;
}


int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> inputVector;
    int m = 0;
    int n = 0;
    int inputValue = 0;
    std::cout << "Enter m of matrix"<< std::endl;
    std::cin>> m;
    std::cout << "Enter n of matrix" << std::endl;
    std::cin >> n;
    for(int i = 0; i < m; i++){
        std::vector<int> temp;
        for(int j = 0; j < n; j++){
            std::cout<<"[" << i<< "]"<<"[" << j<< "]";
            std::cin >> inputValue;
            temp.push_back(inputValue);
        }
        inputVector.push_back(temp);
    }
    int minIter = findMinIteration(inputVector,m,n);
    std::cout << "No of iteration = "<<minIter <<std::endl;
    inputVector.clear();
    return 0;
}
