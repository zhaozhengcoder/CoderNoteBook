#pragma once

#include "helper.h"

class COMM_DEPENDENCY
{
public:
    std::string _name;
};

class RPC: public COMM_DEPENDENCY
{
public:
  virtual void send(const std::string& text) = 0;
};

class GRPC final : public RPC 
{
public:
    void send(const std::string& text) override 
    { 
        std::cout << "[GRPC] " << text << std::endl; 
        // todo
        // use grpc to send data
    }
};

class TRPC final : public RPC 
{
public:
    void send(const std::string& text) override
    { 
       std::cout << "[TRPC] " << text << std::endl; 
        // todo
        // use trpc to send data
    }
};

class LOG: public COMM_DEPENDENCY
{
public:
  virtual void print_log(const std::string& text) = 0;
};

class GLOG final : public LOG 
{
public:
    void print_log(const std::string& text) override 
    { 
        std::cout << "[GLOG] " << text << std::endl; 
    }
};

class XXLOG final: public LOG
{
public:
    void print_log(const std::string& text) override
    { 
        std::cout << "[XXLOG] " << text << std::endl; 
    }
};

REGISTER(GRPC);
REGISTER(TRPC);
REGISTER(GLOG);
REGISTER(XXLOG);
