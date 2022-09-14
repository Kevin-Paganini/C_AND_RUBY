
// Spring 2022
// CS2040
// Professor: Dr.Hasker
// Student: Kevin Paganini
// Date: 3/23/2022







#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include<array>
#include <cstdio>
#include <bits/stdc++.h>
#include <map>

using namespace std;







const int MAX_SIZE = 1000;


//************* METHODS *************

//********************************************************************************
//Prints the array passed in to console (useful for debugging)
//Param: int[] and size of array
void print_array(int x[MAX_SIZE], int size);

//********************************************************************************
//Reads data from standard input into array input
//Param: intialized array that has nothing stored
//Return: Number of elements in the Array
int read_data(int input[MAX_SIZE]);

//********************************************************************************
//Removes outliers and min and max from array
//Param: input array, int min, int max, int size, initialized array for no outliers
//Return: Number of elements in the array
int remove_outliers_and_min_max(int input[MAX_SIZE], 
                                int min, int max, int size,
                                int no_outliers[MAX_SIZE]);


//********************************************************************************
//Check how much a specific number gets called
//Param: an array, number to look for, number of elements in array
//Return: frequency of number to look for in array
int count_frequency(int arr[MAX_SIZE], int num, int size);



//********************************************************************************
//What is the highest value in the array?
//Param: an Array, num_elements in array, frequency count array, int min, int max
//Return: the highest frequency
int get_highest_frequency(int arr[], int size,
                        int freq_count[], int min, int max);
       

//********************************************************************************
//Computes how long lower axis should be
//Param: Highest frequency, an array, and num elements in the array
//Return: Length of the axis
int axis_width(int highest_freq, int arr[], int size);



//********************************************************************************
//Draws the count for a specific value
//Param: int value (before straight line), int quantity (how many hashtags)
//Return: void (it prints)
void draw_count(int value, int quantity);



//********************************************************************************
//Loops through frequency count array and draws the count for a specific value
//Param: int array freq_count, int max, int min
//Return: void (it calls drawCount which prints)
void draw_values(int freq_count[], int max, int min);


//********************************************************************************
//Draws the bottom axis with the "+" and "-"
//Param: int axis_width (how long should i draw)
//Return: void (it prints)
void draw_horizontal_axis(int axis_width);


//********************************************************************************
//Draws axis label
//Param: int axis_width (how long should i draw)
//Return: void (it prints)
void draw_label(int axis_width);


//********************************************************************************
//Calls subroutine to draw histograms
//Param: freq_count array, int max, int min, int axis_width
//Return: void (it prints)
void create_histograms(int freq_count[], int max, int min, int axis_width);



 
void print_array(int x[MAX_SIZE], int size){
    
    cout << "[ ";
    for(int i = 0; i < size; ++i){
        cout << x[i] << ", ";
    }
    cout << "]" << endl;
}






int read_data(int input[MAX_SIZE]){

    int size = 0;
    int number; // current element being read in
    cin >> number; // reading in first number
    while ( cin ){ // while input is being written in

    
    input[size] = number; //Add to array
    
    
    cin >> number; // Read next number
    
    
    ++size; // Making size of array one bigger
    
    }
   
    return size; // Returning the size of the array
}



 
int remove_outliers_and_min_max(int input[MAX_SIZE],
                                int min, int max, int size,
                                int no_outliers[MAX_SIZE]){
    
    int element_count = 0;
    for( int i = 2; i < size; ++i){ //start at 2 to avoid min and max
        if (input[i] <= max && input[i] >= min){ 
            // If element is less than or equal to max and greater or equal to min
            no_outliers[element_count] = input[i]; //adding valid elements to array
            ++element_count;
        } else {
            cout << "Error: value " << input[i] << " is out of range" << endl;
        }
    }
 
    return element_count; // size of no outliers list
}
 


int count_frequency(int arr[MAX_SIZE], int num, int size){
    int count = 0;
    for(int i = 0; i < size; i++){
        if (num == arr[i]){ // if number searching for and value at index match
            count++; //increase the count
        }
    }
    return count; //how many times did target appear in array
}



int get_highest_frequency(int arr[], int size,
                        int freq_count[], int min, int max) {
   
    
    
    
   for(int i = 0; i < size; ++i){
       
       freq_count[arr[i] - min]++; //Making frequency count array
   }
    
    int greatestFreq = 0;
    for(int i = 0; i <= max - min; ++i){
        if (freq_count[i] > greatestFreq){
            greatestFreq = freq_count[i]; //finding greatest value
        }
    }
    
    
        
    return greatestFreq;
    
}



int axis_width(int highest_freq, int arr[], int size){
    
    // Taken from pseudo code
    int axis_width;
    if (highest_freq < 10){
        axis_width = 10;
    } else if (highest_freq %10 == 0){
        axis_width = highest_freq;
    } else {
        axis_width = highest_freq + 10 - (highest_freq % 10);
    }
    return axis_width;
}


void draw_count(int value, int quantity){
    cout << setw(3) << value << flush; // get proper spacing
    cout << " |" << flush; // straight line seperator
    for(int i = 0; i < quantity; i++){ // how many hashtags?
        cout << "#" << flush;
    }
    cout << endl; // make a new line
}


void draw_values(int freq_count[], int max, int min){
    for(int i = max - min; i >=0; i--){
       
        draw_count(i+min, freq_count[i]); // draw value for each element in frequency array
    }
}

void draw_horizontal_axis(int axis_width){
    
    int how_many = axis_width / 10; // how many times should we draw it
    cout << "    +" << flush; // get proper spacing start
    for(int i = 0; i < how_many; i++){
        cout << "----+----+" << flush; //making axis
    }
    cout << endl;
}

void draw_label(int axis_width){ 
    cout << "    " << flush;
    for (int i = 0; i <= axis_width; i+=5){ // Where to draw space or number
        if(i%5 == 0 && i < 10){
            cout << i << flush;
            cout << "    " << flush;
        } else {
            cout << i << flush;
            if(i != axis_width){
                cout << "   " << flush;
            }
            
        }
    }
    cout << endl;
}



void create_histograms(int freq_count[], int max, int min, int axis_width){
    //calls subroutine
    draw_values(freq_count, max, min);
    draw_horizontal_axis(axis_width);
    draw_label(axis_width);
    
}

//MAIN

int main(int argc, char **argv)
{
    
    int input[MAX_SIZE]; // maximum size input array
    int num_elements = read_data(input); // reading data in
        
    
    if (num_elements < 2){ cout << "Not enough elements" << endl;}
    else {
        int max = input[1];
        int min = input[0];
        
        int no_outliers_array[MAX_SIZE];
        //num elements in cleaned array
        int no_outliers_num_elements = remove_outliers_and_min_max(input, min, max, num_elements, no_outliers_array); // clean array
        
        
        int freq_count[max - min +1] = {0}; //initializing frequency array (dictionary would have been easier)
        // highest frequency found
        int most_frequent = get_highest_frequency(no_outliers_array, no_outliers_num_elements, freq_count, min, max); // Gets the highest frequency
        
        //how long should bottom be?
        int axis_w = axis_width(most_frequent, no_outliers_array, no_outliers_num_elements); 
        create_histograms(freq_count, max, min, axis_w); // Draw the output
        
        
        
    }
    
}







