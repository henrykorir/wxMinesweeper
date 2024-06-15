sudo apt-get install -y build-essential libgtk2.0-dev libgtk-3-dev
git clone --recurse-submodules https://github.com/wxWidgets/wxWidgets.git
cd wxWidgets     
mkdir gtk-build             # the name is not really relevant
cd gtk-build
../configure                # builds unicode, shared lib
make -j3                    # use 3 cores. Set to the number of cores your have. 'make' uses 1 core
sudo make install           # some platforms require to use 'su' instead of 'sudo'
sudo ldconfig               # not required in each system