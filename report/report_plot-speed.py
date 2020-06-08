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

	minimum = min(xdata)
	maximum = max(xdata)

	plt.xlim(minimum-0.1, maximum+0.1)

def report(json_data):
	xdata = []
	ydata = []
	
	plt.suptitle("Search speed")
	
	for p in [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]:
		xdata = []
		ydata = []
		for size in range(10, 20):
			for entry in json_data:
				if entry["name"] == 'graph_search(state, "bm/graph-' + str(size) + '-' + str(p) + '.json")':
					xdata.append(size)
					ydata.append(float(entry["cpu_time"]))
		plt.plot(xdata, ydata, marker='o', label=("p=" + str(p)))	
		
	# Subplot 1 ---------------------------------------------------------------
	#  Add data
	#plt.plot(xdata, ydata, color='green', marker='o', label=("node puff"))	
	#  Grid and legend
	plt.grid(True)
	plt.legend()
	#  Make xticks integral and set limits
	plt.yscale("log")
	#configure_xticks(xdata)
	#  Labels
	plt.xlabel('graph size')
	plt.ylabel('search speed (us)')
	
f = open("report-speed.json")
data = json.load(f);
data = data["benchmarks"]

plt.figure(figsize=(20, 10))
report(data);
plt.savefig("plott.png")
plt.show()