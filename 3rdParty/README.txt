How to use the 3rd party libraries for development:

	1. Unzip the *.7z files of the 3rd party libraries for development in the
	same folder of the file 3rdPartyLibConfig.pri.
	
	2. Within a Qt project file, include the file 3rdPartyLibConfig.pri.
	
	3. In order to use one of the 3rd party libraries (e. g. OpenSceneGraph),
	add the following line in the *.pro file of the project (example for OSG):
	
		CONFIG *= WITH_OSG
		
	See the documentation or open the text file 3rdPartyLibrConfig.pri for
	further details.