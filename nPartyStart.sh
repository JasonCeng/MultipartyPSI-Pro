./bin/frontend.exe -n 5 -t 2 -m 12 -p 0 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 1 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 2 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 3 & ./bin/frontend.exe -n 5 -t 2 -m 12 -p 4

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 3 -p 0 > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 3 -p 1 > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 3 -p 2 > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 ./data.bin >> zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data.bin >> zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 ./data.bin >> zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f ./data.bin > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data.bin > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data.bin > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 10 -p 0 -f ./data.bin > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 1 -f ./data.bin > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 2 -f ./data.bin > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 10 -p 0 -f ./data1.bin -ip 192.168.104.202 > zengzc-n3-01.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 1 -f ./data1.bin -ip 192.168.104.202 > zengzc-n3-02.log & ./bin/frontend.exe -n 3 -t 2 -m 10 -p 2 -f ./data1.bin -ip 192.168.104.202 > zengzc-n3-03.log 

./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data1.bin -ip 192.168.104.202 > zengzc-n3-01.log
./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data1.bin -ip 192.168.104.111 > zengzc-n3-02.log
./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f ./data1.bin -ip 192.168.104.116 > zengzc-n3-03.log

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f ./data1.bin -ip 192.168.104.115,192.168.104.116 > zengzc-n3-01.log
./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data1.bin -ip 192.168.104.114,192.168.104.116 > zengzc-n3-02.log
./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data1.bin -ip 192.168.104.114,192.168.104.115 > zengzc-n3-03.log

./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f ./data1.bin -ip 192.168.104.202 > zengzc-n3-01.log
./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data1.bin -ip 192.168.104.202 > zengzc-n3-02.log
./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data1.bin -ip 192.168.104.202 > zengzc-n3-03.log

./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data1.bin -ip 192.168.104.111 > zengzc-n3-02.log
./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data1.bin -ip 192.168.104.116 > zengzc-n3-03.log

# ip应该为数组，包含其他参与方的ip

ufw allow 1200
ufw allow 1201
ufw allow 1202
ufw allow 1203
ufw allow 1301
ufw allow 1302
ufw allow 1303
ufw allow 1401
ufw allow 1402
ufw allow 1403
ufw reload
ufw status
