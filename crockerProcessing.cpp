// Name: Luke Crocker
// Class: CPE 381
// Instructor: Dr. Emil Jovanov
// Filename: crockeProcessing.cpp
// Phase 1 Due: October 8, 2018
// Phase 2 Due: November 26, 2018
// Program: Reading samples to apply FIR filter
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstddef>
#include "filter.h"

using namespace std;

int main()
{

	clock_t s_time; //Start Time
 	clock_t e_time; //End Time

	FILE* fPointer1; //Input File Stream
	FILE* fPointer2; //Output File Stream
	string filename1 = "Crocker_L_Mod.wav";
	string filename2 = "Crocker_L_Proc.wav";

	char typeStr1[4]; //RIFF
	char typeStr2[4]; //WAVE
	char typeStr3[4]; //frt[SPACE]
	char typeStr4[4]; //data
	
	unsigned int size; //Size of File
	unsigned short int numberOfBitsPerSample;
	unsigned short int numberOfBytesPerSample;  
	unsigned short int format; //PCM

	unsigned int chunkSize;
	unsigned int averBytesPerSec;
	unsigned int size2; //Size of Data

	unsigned short int channels; //# of Channels
	unsigned int Fs; //Sampling Frequency

	s_time = clock();
	fPointer1 = fopen(filename1.c_str(), "r"); 

	//Reading Header
	fread(typeStr1, sizeof(char), 4, fPointer1);
	fread(&size, sizeof(int), 1, fPointer1);
	fread(typeStr2, sizeof(char), 4, fPointer1);
	fread(typeStr3, sizeof(char), 4, fPointer1);
	fread(&chunkSize, sizeof(int), 1, fPointer1);
	fread(&format, sizeof(short int), 1, fPointer1);
	fread(&channels, sizeof(short int), 1, fPointer1);
	fread(&Fs, sizeof(int), 1, fPointer1);
	fread(&averBytesPerSec, sizeof(int), 1, fPointer1);
	fread(&numberOfBytesPerSample, sizeof(short int), 1, fPointer1);
	fread(&numberOfBitsPerSample, sizeof(short int), 1, fPointer1);
	fread(typeStr4, sizeof(char), 4, fPointer1);
	fread(&size2, sizeof(int), 1, fPointer1);

	fPointer2 = fopen(filename2.c_str(), "wb"); //Open output file stream
	if (channels == 1)
	{
		//Add input header to output file
		fwrite(typeStr1, sizeof(char), 4, fPointer2);
		fwrite(&size, sizeof(int), 1, fPointer2);
		fwrite(typeStr2, sizeof(char), 4, fPointer2);
		fwrite(typeStr3, sizeof(char), 4, fPointer2);
		fwrite(&chunkSize, sizeof(int), 1, fPointer2);
		fwrite(&format, sizeof(short int), 1, fPointer2);
		fwrite(&channels, sizeof(short int), 1, fPointer2);
		fwrite(&Fs, sizeof(int), 1, fPointer2);
		fwrite(&averBytesPerSec, sizeof(int), 1, fPointer2);
		fwrite(&numberOfBytesPerSample, sizeof(short int), 1, fPointer2);
		fwrite(&numberOfBitsPerSample, sizeof(short int), 1, fPointer2);
		fwrite(typeStr4, sizeof(char), 4, fPointer2);
		fwrite(&size2, sizeof(int), 1, fPointer2);
		
		int numSamples = (size/2) + 10; //Calculated number of samples
		short int* sample = new short int;
		short int inputSamples[numSamples];
		short int *outputSample = new short int;
		fread(&(*sample), sizeof(short int), 1, fPointer1);
		cout << "Processing Samples ... " << endl; 
		while (!feof(fPointer1)) //Test for end of input file
		{
			real64_T tempr = 0.0; //real64_T defined in tmwtypes.h included by filter.h

			for (int i = BL - 1; i > 0; i--) //Shifting samples in buffers
			{
				inputSamples[i] = inputSamples[i-1];
			} 

			inputSamples[0] = *sample; 
			for (int j = 0; j < BL; j++) //Convolution sum
			{
				tempr += inputSamples[j]*B[j];
			} 
			if (tempr < -32768) //Preventing overflow
				*outputSample = -32768;
			else if (tempr > 32767) 
				*outputSample = 32767;
			else
				*outputSample = short(tempr); 
			fwrite(&(*outputSample), sizeof(short int), 1, fPointer2);
			fread(&(*sample), sizeof(short int), 1, fPointer1);
		}
		delete sample;
		sample = NULL;
		delete outputSample;
		outputSample = NULL;

	}
	else
	{
		cout << endl << "This program only processes one channel." << endl << endl;
	}

	fclose(fPointer1);
	fclose(fPointer2);
	e_time = clock();

	cout << endl << "Execution Time: " << float(e_time - s_time)/CLOCKS_PER_SEC << " sec" << endl << endl;

}


