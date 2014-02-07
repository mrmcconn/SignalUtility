This is the SignalUtility developed by McConnell using Visual Studio Express 2013.

The installer for this tool is in the works; it is a cumbersome process when using C++ with Visual Studio Express.

To use the tool, run it from Visual Studio Express 2013 and click "Load Signal." The signal should be a text file with the number of data points on the first line and then the x and y values of the points, respectively, on each subsequent line, delimited by whitespace.

When the data has loaded, it will be displayed on a line chart in the window. The next step is to select a smoothing vector width from the drop box on the bottom right of the window and click "Smooth Signal". The signal, subject to Gaussian blur, will be displayed in red over the original signal. The field marked "Ratio of greatest extrema:" indicates the fidelity of the altered signal. The lower this value is, the greater the distortion there is from the source.

At any time, you may remove the smoothed signal from the screen by clicking "Display Original Signal", and you may display the smoothed signal, again, by clicking "Smooth Signal".

When you are satisfied with the level of noise reduction, click "Save Adjusted Signal" to write the adjusted signal to file. The adjusted signal will be saved to file in the same format as the original signal WITH TWO EXCEPTIONS: 1) the number of data points will not be written to file and 2) each x and y pair will be delimited with exactly two spaces. This is consistent with the fomat required by the QuadFit NMR spectrum simulator developed by Thomas Kemp of the University of Warwick.