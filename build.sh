
#!/bin/sh
#  Build and install iBase 1.4c1 and dependent products

#  Set the IBASE variable to the installation directory
if [ -z "$IBASE" ]; then
    echo 'The IBASE environment variable is not defined.'
    echo 'Set this to desired installation directory, e.g. $HOME/ibase.'
    echo 'Then, add $IBASE/bin to your PATH for best results.'
    exit 1
fi

#   Build foreign
cd foreign
sh ./boomake build test install;
if [ $? != 0 ]; then
    echo "E: Build of foreign failed" 1>&2
    exit 1
fi
cd ..

#   Build base1
cd base1
sh ./boomake build test install;
if [ $? != 0 ]; then
    echo "E: Build of base1 failed" 1>&2
    exit 1
fi
cd ..

#   Build gsl4
cd gsl4
sh ./boomake build test install;
if [ $? != 0 ]; then
    echo "E: Build of gsl4 failed" 1>&2
    exit 1
fi
cd ..

#   Build base2
cd base2
sh ./boomake build test install;
if [ $? != 0 ]; then
    echo "E: Build of base2 failed" 1>&2
    exit 1
fi
cd ..

#   Done successfully
echo "Finished building and installing iBase 1.4c1."

