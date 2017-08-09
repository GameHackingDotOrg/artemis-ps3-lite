# gui
Frontend of Artemis PS3 Lite.


# Dependencies
	        PSL1GHT SDK (https://github.com/HACKERCHANNEL/PSL1GHT)
	        Tiny3D (https://github.com/wargio/tiny3D)
	        Mini2D (https://github.com/Dnawrkshp/mini2d)


# Build
~~~~
make
~~~~

# Run with PS3Load
~~~~
make run
~~~~

# Run with RPCS3
You need RPCS3 installed and the environment variable 'RPCS3' set to the path of your RPCS3 executable.

You can do this by adding the following to your /etc/profile (MinGW) or .bashrc (linux)
~~~~
export RPCS3="PATH_TO_RPCS3_EXECUTABLE"
~~~~

Finally you can build and run.
~~~~
make rpcs3
~~~~

# Package
~~~~
make pkg
~~~~
