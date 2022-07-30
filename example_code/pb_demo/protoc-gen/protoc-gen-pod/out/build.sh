#!/bin/bash
rm test_main
g++ *.cpp proto/*.cc -o test_main -L/usr/local/lib -lprotobuf -lpthread -I. -Iproto

# g++ demo.cpp heartbeat.cpp machine.cpp test_main.cpp proto/custom_opt.pb.cc proto/demo.pb.cc proto/heartbeat.pb.cc proto/machine.pb.cc -o test_main -L/usr/local/lib -lprotobuf -lpthread -I. -Iproto