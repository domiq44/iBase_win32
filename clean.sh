
#!/bin/sh
#  Clean iBase 1.4c1 and dependent products

#  Set the IBASE variable to the installation directory
if [ -z "$IBASE" ]; then
    echo 'The IBASE environment variable is not defined.'
    echo 'Set this to desired installation directory, e.g. $HOME/ibase.'
    echo 'Then, add $IBASE/bin to your PATH for best results.'
    exit 1
fi

#   Clean foreign
cd foreign
sh ./boomake clean;
if [ $? != 0 ]; then
    echo "E: Clean of foreign failed" 1>&2
    exit 1
fi
cd ..

#   Clean base1
cd base1
sh ./boomake clean;
if [ $? != 0 ]; then
    echo "E: Clean of base1 failed" 1>&2
    exit 1
fi
cd ..

#   Clean gsl4
cd gsl4
sh ./boomake clean;
if [ $? != 0 ]; then
    echo "E: Clean of gsl4 failed" 1>&2
    exit 1
fi
cd ..

#   Clean base2
cd base2
sh ./boomake clean;
if [ $? != 0 ]; then
    echo "E: Clean of base2 failed" 1>&2
    exit 1
fi
cd ..

#   Done successfully
echo "Finished cleaning iBase 1.4c1."

