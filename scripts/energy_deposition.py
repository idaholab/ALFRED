# Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED
# This script creates a pandas DataFrame with the energy deposition output as a function of time.

import numpy as np
import pandas as pds
import sys

# Function to check if a string can be converted to a float
def is_float(string):
    try:
        float(string)
        return True
    except ValueError:
        return False

# Number of inactive batches to skip
inactive_batches = 5

# Get the listing file from the command-line arguments
listing_file = sys.argv[1]

# Read the entire content of the listing file
with open(listing_file, 'r') as f:
    txt = f.read()

# Initialize an empty string to hold lines starting with "RUN"
runListing = ""
lines = txt.split("\n")
for line in lines:
    if "RUN" == line[:3]:
        runListing = runListing + line + '\n'

# Remove the last newline character
runListing = runListing[:-1]

# Initialize an empty dictionary to store results
results = {}

# Split the runListing into lines
lines = runListing.split("\n")
for batch in range(0, len(lines)):
    line = lines[batch]
    args = line.split(' ')
    # Process lines after the inactive batches
    if batch >= inactive_batches: 
        for i in range(1, len(args) // 2):
            label = str(args[2*i])
            value = float(args[2*i + 1])
            if label not in results.keys():
                results[label] = []
            results[label].append(value)

# Initialize lists to store means and standard deviations of energy values and times
energyListMean, energyListStd = [], []
timeList = []

# Iterate through the results dictionary
for key, values in results.items():
    # Check if the key represents a time value
    if is_float(key[:-1]):
        timeList.append(float(key[:-1]))
        energyValues = []
        # Normalize energy values by dividing by the corresponding tFission value
        for i in range(0, len(values)):
            energyValues.append(values[i] / results["tFission:"][i])
        # Compute mean and standard deviation of the normalized energy values
        energyListMean.append(np.mean(energyValues))
        energyListStd.append(np.std(energyValues))

# Compute time differences between consecutive time points
timeDelta = np.array(timeList[1:]) - np.array(timeList[:-1])
timeArray = np.array(timeList[1:])

# Remove the last element from energyListMean and energyListStd to align with timeDelta
energyDepositionMean = np.array(energyListMean[:-1])
energyDepositionStd = np.array(energyListStd[:-1])

# Create a dataset dictionary with the calculated values
dataset = {
    "time": timeArray,
    "energy deposited": energyDepositionMean,
    "uncertainty": energyDepositionStd,
    "energy per second": energyDepositionMean / timeDelta,
    "cumulated energy": np.cumsum(energyDepositionMean)
}

# Convert the dataset dictionary to a pandas DataFrame
df = pds.DataFrame.from_dict(dataset)

# Save the DataFrame to a CSV file
df.to_csv('EnergyDeposition.csv', index=False)

# Print the DataFrame to the console
print(df)