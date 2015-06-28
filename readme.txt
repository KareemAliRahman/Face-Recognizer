
-------
Authors
-------
Kareem Ali
Ahmad Hassan 
Mina Sokrat

----------------
C implementation
----------------
In order to overcome the pythons huge run time limitations we implemented the most
exhaustive function which is the Lbp in c++ and interfaced it with our python impl-
ementation so we call the function lbp from the shared library lbp we wrote for every
image. The shared library as will as a makefile you can edit for your machine requirements
are available in the same folder make sure you include them.

-------
Running
-------
Make sure that the folders "negative train", "Positive train" and "test" are all available in
the same folder and simpy run Facedetector.py

------
Output
------
The output is total runtime in seconds
Precision
Recall
F1 Measure
