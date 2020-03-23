import matplotlib.pyplot as plt
import numpy as np
import time

# start recording time for gathering data & visualization
start = time.time()

list_numSamples= []
list_sampleFrequencies=[]

with open("../output/info.log") as f:
    lines = f.readlines()
    numSamplesString= lines[9:10:1]
    string = numSamplesString[0]

# numsamples = int(string.split(":",1)[1], 10)
numsamples = 5000

for x in range(numsamples):
    list_numSamples.append(x)



output = open("../output/output.txt")
for x in range(numsamples):
    list_sampleFrequencies.append(output.readline())




# we want a proportional number of ticks on y axis so it does not get bloated
# plt.yticks(np.arange(min(list_numSamples), max(list_numSamples)+1, np.log(numsamples)))

# plt.axis('off')
fig = plt.figure(figsize=(20, 10))
ax = fig.add_subplot(111)

plt.plot(list_numSamples, list_sampleFrequencies)
plt.xlabel('Sample number')
plt.ylabel('Sampling frequency')

plt.yscale("log")

plt.savefig("../output/plot.png")
plt.show()
end = time.time()

with open("../output/info.log") as f:
    lines = f.readlines()
lines[13] = "Time elapsed for audio data visualization: " + str(round(end-start, 5)) + " seconds\n";

# write everything back
with open("../output/info.log", 'w') as file:
    file.writelines(lines)
f.close()
