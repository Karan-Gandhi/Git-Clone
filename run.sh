rm -r ./.gitc
./bin/gitc init
rm ./hello.txt
touch ./hello.txt
./bin/gitc add hello.txt
./bin/gitc commit -m "Initial commit"
echo "Hello World 2" > ./hello.txt
./bin/gitc add hello.txt
./bin/gitc commit -m "Second commit"
./bin/gitc log