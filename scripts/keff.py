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

# print keff results
keffMean = np.mean(results["keff:"])
keffStd = np.std(results["keff:"])
print(f"keff: {keffMean:.5f} +/- {keffStd:.5f}")