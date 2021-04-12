#! /bin/bash

# print all inputted terms
echo number of inputted terms: $#
echo terms: $*


#copy file to file
cpf2f() 
{

#if the source file doesn't exist
if [ ! -e $1 ]; then
echo no such source file $1
return 1
fi

#if the source and destination files are the same
if [ $1 -ef $2 ]; then
echo "never copy a fiile to itself"
return 1
fi

#copy
if [ -L $1 ]; then
echo "copying symlink $1"
link=$(readlink $1)
ln -s $link $2
return 0
fi

echo "copying $1 to $2"
cp $1 $2 2> /dev/null
}


#copy file to directory
cpf2d()
{
newfile=$2/$(basename $1)
cpf2f $1 $newfile
}

#copy directory to directory
cpd2d()
{
newFile1=$1/$(basename $2)
cpf2d $newFile1 $2
}

cpd2d $1 $2

# **************************** entry point of myrcp ******************************
# case analysis
# for each f1 to fn-1, call cpf2f() or cpf2d() or cpd2d()

