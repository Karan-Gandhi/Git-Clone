rm -r ./.gitc
./bin/gitc init
echo "Hello World" > ./hello.txt
./bin/gitc add hello.txt
./bin/gitc commit -m "Initial commit"
echo "Hello World 2" > ./hello.txt
./bin/gitc add hello.txt
./bin/gitc commit -m "Second commit"
./bin/gitc log