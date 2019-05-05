import matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict
import json

def configure_xticks(xdata):
	xint = []
	locs, labels = plt.xticks()
	for each in locs:
		xint.append(int(each))
	plt.xticks(xint)

	minimum = min(xdata[next(iter(xdata))])
	maximum = max(xdata[next(iter(xdata))])
	for key in xdata:
		minimum = min(minimum, min(xdata[key]))
		maximum = max(maximum, max(xdata[key]))

	plt.xlim(int(minimum-1), int(maximum+1))

def report(json_data, n):
	xdata   = []
	ydata1a = []
	ydata1b = []
	ydata2a = []
	ydata2b = []
	
	for entry in json_data:
		if entry["source"]["graph_size"] == n:
			xdata  .append(float(entry["source"]["graph_target_ratio"]))
			ydata1a.append(float(entry["result"]["node_puff_clusters"]))
			ydata1b.append(float(entry["result"]["edge_puff_clusters"]))
			ydata2a.append(float(entry["result"]["node_puff_edges"]))
			ydata2b.append(float(entry["result"]["edge_puff_edges"]))
		
	plt.suptitle("Graph size (n): {}".format(n))
		
	# Subplot 1 ---------------------------------------------------------------
	plt.subplot(1, 2, 1)
	#  Add data
	plt.plot(xdata, ydata1a, color='green', marker='o', label=("node puff"))		
	plt.plot(xdata, ydata1b, color='red',   marker='o', label=("edge puff"))		
	#  Grid and legend
	plt.grid(True)
	plt.legend()
	#  Make xticks integral and set limits
	plt.yscale("log")
	#configure_xticks(xdata)
	#  Labels
	plt.xlabel('graph ratio')
	plt.ylabel('puff clusters')

	# Subplot 1 ---------------------------------------------------------------
	plt.subplot(1, 2, 2)
	#  Add data
	plt.plot(xdata, ydata2a, color='green', marker='o', label=("node puff"))		
	plt.plot(xdata, ydata2b, color='red',   marker='o', label=("edge puff"))		
	#  Grid
	plt.grid(True)
	plt.legend()
	#  Make xticks integral and set limits
	plt.yscale("log")
	#configure_xticks(xdata)
	#  Labels
	plt.xlabel('graph ratio')
	plt.ylabel('puff edges')
	
f = open("report-7-8-9-10.json")
data = json.load(f);

for n in [7, 8, 9, 10]:
	plt.figure(figsize=(20, 10))
	report(data, n);
	plt.savefig("plot-n{}.png".format(n))
	plt.show()