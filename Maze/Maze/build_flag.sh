FLAG=""

if [[ $3 ]]
then
	FLAG="-DPRINT"
fi

gcc generation.c $FLAG -o gen.out
echo $1 $2
time ./gen.out $1 $2
