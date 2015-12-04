# HistoGui
##A graphical tool for particle physics data analysis.

Given series of events in ROOT data file, the program allows to plot histograms and apply 
cutoffs to each histogram with wxWidgets based GUI. 

Data are stored in multiplexed binary files,
i.e. one needs to create such file from ROOT branch and JSON configuration file, employing provided command line tool. The GUI application uses the very same JSON config, when loading binary data.

Example JSON configuration file and small ROOT file with junk data are provided in DataIO folder.JSON contains an arbitrary number of first level nodes (in the example there is one called "dat_file1"). 
Below we have "option" node, comprising self-evident description of our files structure i.e. ROOT file, tree, and branch names, number of events to process and save in binary file,and binary file name. Second node at this level, "histos" contains the array of histogram descriptions, comprised of histogram name, the number of bins, and the range of values one can put in the histogram. In this case the range is redundant for now, since multiplexed values are equal to specific number of bins, but it makes the GUI application more universal. 

To generate a binary datafile one needs to build ParseTree program, specifying path to the 
ROOT config tool in DataIO/Makefile and running
``` make ParseTree``` 
in DataIO directory, provide config.json file and run the tool, typing just:

``` ./ParseTree ```
 
Then to run the GUI one needs to build data access shared library and the GUI itself, typing 
```make```
in DataIO and HistogramGui dirs, and copy config.json and generated binary data file to HistogramGui directory.


