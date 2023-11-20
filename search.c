#include <stdio.h>


int binary_search(int arr[] , int size , int key ){
    int l = 0 , r = size - 1 ;
    while(l < r){
        int mid = l + (r-l)/2;
        if(arr[mid] == key){
            return mid;
        }else if(arr[mid] < key){
            l = mid;
        }else{
            r = mid;
        }
    }

    return -1;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10} ;

    printf("%d\n",binary_search(arr,10,3));
}