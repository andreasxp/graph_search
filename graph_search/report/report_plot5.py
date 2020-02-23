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
			max_edges_source = n*(n-1)/2
			max_edges_line = float(entry["result"]["line_graph_size"])*(float(entry["result"]["line_graph_size"])-1)/2
		
			xdata  .append(float(entry["source"]["graph_target_ratio"]))
			ydata1a.append(float(entry["result"]["line_graph_size"]) / float(entry["source"]["graph_size"]))
			ydata2a.append((float(entry["result"]["line_graph_ratio"])*max_edges_line) / (float(entry["source"]["graph_target_ratio"])*max_edges_source))
		
	plt.suptitle("Graph size (n): {}".format(n))
		
	# Subplot 1 ---------------------------------------------------------------
	plt.subplot(1, 2, 1)
	#  Add data
	plt.plot(xdata, ydata1a, color='green', marker='o', label=("line graph"))		
	#plt.plot(xdata, ydata1b, color='red',   marker='o', label=("edge puff"))		
	#  Grid and legend
	plt.grid(True)
	#plt.legend()
	#  Make xticks integral and set limits
	#plt.yscale("log")
	#configure_xticks(xdata)
	#  Labels
	plt.xlabel('graph ratio')
	plt.ylabel('line graph size to source graph size')

	# Subplot 1 ---------------------------------------------------------------
	plt.subplot(1, 2, 2)
	#  Add data
	plt.plot(xdata, ydata2a, color='green', marker='o', label=("line graph"))		
	#plt.plot(xdata, ydata2b, color='red',   marker='o', label=("edge puff"))		
	#  Grid
	plt.grid(True)
	#plt.legend()
	#  Make xticks integral and set limits
	#plt.yscale("log")
	#configure_xticks(xdata)
	#  Labels
	plt.xlabel('graph ratio')
	plt.ylabel('line graph edges to source graph edges')
	
f = open("report n{7, 8}p{0.1-0.9@0.1} + n{9, 10}p{0.1-0.5@0.1}.json")
data = json.load(f);

for n in [7, 8]:
	plt.figure(figsize=(20, 10))
	report(data, n);
	plt.savefig("plot-n{}.png".format(n))
	plt.show()