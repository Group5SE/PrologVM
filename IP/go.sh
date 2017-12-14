#echo go.sh <name_of_prog> assumed in dir ./progs
mkdir out
mkdir out/production
export TARGET="out/production/IP"
mkdir "$TARGET"
rm -r -f $TARGET/iProlog
rm -f progs/*.pl.nl
g++ -o object src/iProlog/*.cpp -std=c++11
swipl -f pl2nl.pl -g "pl('$1'),halt"
./object "progs/$1.pl"
ls progs/*.pl
rm -f object
