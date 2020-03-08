#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>

using namespace std;

int bin = 0;
bool show_chunk_size = false;
bool show_format_type = false;
bool show_num_channels = false;
bool show_sample_rate = false;
bool show_avg_bytes_per_sec = false;
bool show_bytes_per_sample = false;
bool show_bits_per_sample = false;
bool show_data_size = false;
bool show_length = false;
bool show_num_samples = false;

class audio {

public:

  void OpenFile(FILE ** fp1, const char * fname, const char * mode)
  {
      *fp1 = fopen(fname, mode);
  }

  void CheckConditions(int argc, char**argv){
    if(argc==1){
      cout << "Usage: " << argv[0] << " <file.wav> -info <info> -mode <mode>\n" <<endl;
      exit(1);
    }
    else if (argc == 4 && strcmp("-info", argv[2]) == 0){
        if(strcmp("chunk_size", argv[3]) ==0){
          show_chunk_size = true;
        }
        else if (strcmp("format_type", argv[3]) ==0) {
          show_format_type = true;
        }
        else if (strcmp("num_channels", argv[3]) ==0) {
          show_num_channels = true;
        }
        else if (strcmp("sample_rate", argv[3]) ==0) {
          show_sample_rate = true;
        }
        else if (strcmp("avg_bytes_per_sec", argv[3]) ==0) {
          show_avg_bytes_per_sec = true;
        }
        else if (strcmp("bytes_per_sample", argv[3]) ==0) {
          show_bytes_per_sample = true;
        }
        else if (strcmp("bits_per_sample", argv[3]) ==0) {
          show_bits_per_sample = true;
        }
        else if (strcmp("data_size", argv[3]) ==0) {
          show_data_size = true;
        }
        else if (strcmp("length", argv[3]) ==0) {
          show_length = true;
        }
        else if (strcmp("num_samples", argv[3]) ==0) {
          show_num_samples = true;
        }
        else {
          cout << "\nThat command line argument is not recognized.\nChoose from one of the following: chunk_size,"
          << " format_type," <<" num_channels,"<< " sample_rate," <<" avg_bps," <<" bytes_per_sample,"
          <<" bits_per_sample,"<<" data_size," <<" length," <<" num_samples\n" << endl;
          exit(1);
        }
    }
  }

};

audio audio;

int main(int argc, char**argv) {
    FILE *fp1 = NULL;
    audio.CheckConditions(argc, argv);
    audio.OpenFile(&fp1, argv[1], "rb"); //binary mode
    if (!fp1)
    {
        cout << "Error: missing or bad file" << endl;
        return 1;
    }

    // initializing the variables we will be using
    short format_type, channels;
    int sample_rate, avg_bytes_per_sec;
    short bytes_per_sample, bits_per_sample;
    char type_4[5] = {0}; // "data"
    int data_size;
    char type_1[5] = {0};
    char type_2[5] = {0};
    char type_3[5] = {0};
    int size, chunk_size;

    // check for RIFF format
    fread(type_1, sizeof(char), 4, fp1);
    if (strcmp(type_1, "RIFF"))
    {
        cout << "Error: not RIFF format";
        return 1;
    }

    fread(&size, sizeof(int), 1, fp1);
    // check for WAVE format
    fread(type_2, sizeof(char), 4, fp1);
    if (strcmp(type_2, "WAVE"))
    {
        cout << "Error: not WAVE format";
        return 1;
    }

    // check for "fmt " string
    fread(type_3, sizeof(char), 4, fp1);
    if (strcmp(type_3, "fmt "))
    {
        cout << "Error: missing format string";
        return 1;
    }

    fread(&chunk_size, sizeof(int), 1, fp1);
    fread(&format_type, sizeof(short), 1, fp1);
    fread(&channels, sizeof(short), 1, fp1);
    fread(&sample_rate, sizeof(int), 1, fp1);
    fread(&avg_bytes_per_sec, sizeof(int), 1, fp1);
    fread(&bytes_per_sample, sizeof(short), 1, fp1);
    fread(&bits_per_sample, sizeof(short), 1, fp1);

    if(show_chunk_size == true){
      cout << chunk_size << endl;
      exit(1);
    }
    else if(show_format_type == true){
      cout << format_type << endl;
      exit(1);
    }
    else if(show_num_channels == true){
      cout << channels << endl;
      exit(1);
    }
    else if(show_sample_rate == true){
      cout << sample_rate << endl;
      exit(1);
    }
    else if(show_avg_bytes_per_sec == true){
      cout << avg_bytes_per_sec << endl;
      exit(1);
    }
    else if(show_bytes_per_sample == true){
      cout << bytes_per_sample << endl;
      exit(1);
    }
    else if(show_bits_per_sample == true){
      cout << bits_per_sample << endl;
      exit(1);
    }

    // check for "data" string
    fread(type_4, sizeof(char), 4, fp1);
    if (strcmp(type_4, "data"))
    {
        cout << "Error: missing data string";
        return 1;
    }
    fread(&data_size, sizeof(int), 1, fp1);

    // create our infodump file
    ofstream file_infoLog("../output/info.log");

    // output
    file_infoLog << "File name and path: " << argv[1] << endl;
    file_infoLog << "Chunk size: " << chunk_size << endl;
    file_infoLog << "Format type: " << format_type << endl;
    file_infoLog << "Number of channels: " << channels << endl;
    file_infoLog << "Sample rate: " << sample_rate << endl;
    file_infoLog << "Average bytes per second: " << avg_bytes_per_sec << endl;
    file_infoLog << "Bytes per sample: " << bytes_per_sample << endl;
    file_infoLog << "Bits per sample: " << bits_per_sample << endl;
    file_infoLog << "Data size: " << data_size <<" bytes"<<endl;
    unsigned long long number_of_samples = data_size/bytes_per_sample;

    std::vector<short> samples(number_of_samples);
    unsigned long long elements_read = fread(samples.data(), sizeof(short), number_of_samples, fp1);

    if(show_data_size == true){
      cout << data_size <<" bytes"<<endl;
      exit(1);
    }
    else if(show_length == true){
      cout << number_of_samples / sample_rate << " seconds\n";
      exit(1);
    }
    else if(show_num_samples == true){
      cout << elements_read << endl;
      exit(1);
    }

    fclose(fp1);

    file_infoLog << "Audio length: " << number_of_samples / sample_rate << " seconds\n";
    file_infoLog << "Total number of samples read: " << elements_read << "\n\n";


    bitset<16> bitNumb=0;
    ofstream OutFile("../output/output.txt");
    ofstream OutBin("../output/output-bin.txt");
    // start recording time
    // main computation here
    clock_t begin = clock();
    for (unsigned long long i = 0; i<number_of_samples; i++)
    {
        bitNumb = samples[i];
        OutBin << bitNumb.to_string() << '\n';
        OutFile << samples[i] << '\n';
    }

    // end recording
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    file_infoLog << "Time elapsed for audio data extraction: " << elapsed_secs << " seconds"<< endl << endl;
    OutFile.close();

    return 0;
}
