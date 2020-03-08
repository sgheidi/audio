## Prerequisites

Verify that the current Python version is Python 3.x by typing ```python3 --version```.
Install the following core packages required to run the Python visualization components:
```
pip install matplotlib
pip install numpy
```

## The program

The program consists of two components: the main C++ source file (main.cc), which performs the data analysis, and the Python source (plot.py) which visualizes the extracted data.

There are also audio files in the 'test_audio' folder which can be used for testing.

## Running the program

After setting up the required packages and navigating to the 'src' directory, use the main program by running:
```
make && ./main <path_to_file> -info <info>
```
For the Python visualization component, run:
```
python3 plot.py
```
All output files are stored in the 'output' directory.

## Example usage

A simple example of using the program is running ```./audio ../test_audio/mono.wav``` followed by ```python3 plot.py```.
Some other examples, using additional command line arguments, are:

```
./main ../test_audio/song.wav -info chunk_size
./main ../test_audio/mono.wav -info num_samples
```

Note that the second command-line argument is optional; an audio file path at minimum is required to run the program.
The -info switch can take the following arguments:
chunk_size, format_type, num_channels, sample_rate, avg_bps, bytes_per_sample, bits_per_sample, data_size, length, num_samples

## Other notes

- This command-line tool only works on RIFF audio data (i.e the '.wav' file extension).
- The plot only shows the first 5000 samples to save computational time, as the audio signal is periodic.
- Code is well commented, separated into objects and uses powerful visualization library (Python's matplotlib) to visualize the signal data.
