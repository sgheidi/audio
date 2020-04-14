# 🔊 audio 🔊

## Prerequisites

Run ```pip install -r requirements.txt```

## The program

The program consists of two components: the main C++ source file (main.cc), which performs the data analysis, and the Python source (plot.py) which visualizes the extracted data.

## Running the program

After navigating to the 'src' directory, use the main program by running:
```
make; ./audio <path_to_file> -info <info>
```
For the Python visualization component, run:
```
py plot.py
```
All results are stored in the 'output' directory.

## Example usage

A simple example of using the program is running ```./audio ../test_audio/mono.wav``` followed by ```py plot.py```.
Some other examples, using additional command line arguments, are:

```
./audio ../test_audio/song.wav -info chunk_size
./audio ../test_audio/mono.wav -info num_samples
```

The ```-info``` switch can take the following arguments:
chunk_size, format_type, num_channels, sample_rate, avg_bps, bytes_per_sample, bits_per_sample, data_size, length, num_samples

## Other notes

- This command-line tool only works on RIFF audio data (i.e the '.wav' file extension).
- The plot only shows the first 5000 samples to save computation time, as the audio signal is periodic.
