./bin/frontend.exe -n 5 -t 2 -m 12 -p 0 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 1 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 2 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 3 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 4

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 3 -p 0 > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 3 -p 1 > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 3 -p 2 > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 ./data.bin >> zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data.bin >> zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 ./data.bin >> zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f ./data.bin > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data.bin > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data.bin > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 10 -p 0 -f ./data.bin > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 1 -f ./data.bin > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 2 -f ./data.bin > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 10 -p 0 -f ./data1.bin > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 1 -f ./data1.bin > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 2 -f ./data1.bin > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f './data.bin'
./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f './data.bin'
./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f './data.bin'