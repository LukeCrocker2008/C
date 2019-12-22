// Name: Luke Crocker
// Class: CPE 381
// Instructor: Dr. Emil Jovanov
// Filename: crockerCPE381.cpp
// Phase 1 Due: October 8, 2018
// Phase 2 Due: November 26, 2018
// Program: Reading samples from audio file
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstddef>

using namespace std;

const float PI = 3.141593;

int main()
{
	clock_t s_time; //Start Time
 	clock_t e_time; //End Time	

	FILE* fPointer1; //Input File Stream
	FILE* fPointer2; //Output File Stream
	string filename1 = "Crocker_L_Orig.wav";
	string filename2 = "Crocker_L_Mod.wav";

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

	float t = 0.0; // nTs

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

		float noise1 = 3276.7*sin(2*PI*(1600)*t);	
		float noise2 = 3276.7*sin(2*PI*(2400)*t + (PI/3));
		short int *currentSample = new short int;
		short int *previousSample = new short int;
		int averageSample;
		short int *writeSample = new short int;	

		fread(&(*currentSample), sizeof(short int), 1, fPointer1); //Priming read
		*previousSample = *currentSample;
		fread(&(*currentSample), sizeof(short int), 1, fPointer1);
		while (!feof(fPointer1)) //Test for end of input file
		{
			t = t + (1.0/Fs); //Time related to number of samples
			noise1 = 3276.7*sin(2*PI*(1600)*t);	
			noise2 = 3276.7*sin(2*PI*(2400)*t + (PI/3));	
			averageSample = (*previousSample + *currentSample)/2 + int(noise1 + noise2); //Make average of current and previous sample and add noise 
			if (averageSample < -32768) //Preventing overflow
				*writeSample = -32768;
			else if (averageSample > 32767) 
				*writeSample = 32767;
			else
				*writeSample = short(averageSample);
			fwrite(&(*writeSample), 2, 1, fPointer2);
			*previousSample = *currentSample;
			fread(&(*currentSample), 2, 1, fPointer1);
		}

		delete currentSample;
		currentSample = NULL;
		delete previousSample;
		previousSample = NULL;
		delete writeSample;
		writeSample = NULL;
	}
	else
	{
		cout << endl << "This program only processes one channel." << endl << endl;
	}

	fclose(fPointer1);
	fclose(fPointer2);
	e_time = clock();

	ofstream outFile; //Summary Text File
	outFile.open("summary.txt");
	if (channels == 1)
	{
		outFile << "Filename: " << filename1 << endl;
		outFile << "Sampling Frequency: " << Fs << " Hz" << endl;
		outFile << "Channels: " << channels << endl;
		outFile << "Bits per Sample: " << numberOfBitsPerSample << endl;
		outFile << "Size of file: " << size << endl;
		outFile << "Size of Data: " << size2 << endl;
		outFile << "Record length of Time: " << t << " sec" << endl;
		outFile << "Execution Time: " << float(e_time - s_time)/CLOCKS_PER_SEC << " sec" << endl;
	}
	else
	{
		outFile << "This program only processes one channel." << endl;
		outFile << "Execution Time: " << float(e_time - s_time)/CLOCKS_PER_SEC << " sec" << endl;
	}

	outFile.close();

	return 0;
}
