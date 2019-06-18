// Copyright 2017 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");

// Except for formatting, comments, and portability, this was copied
// from projects/example/my-api-repo/standalone_fuzz_target_runner.cpp
// in https://github.com/oss-fuzz

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(unsigned char const* data, size_t size);

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        std::ifstream in(argv[i]);
        in.seekg(0, in.end);
        size_t length = in.tellg();
        in.seekg (0, in.beg);
        std::cout << "checking " << argv[i] << std::endl;
        // Allocate exactly length bytes so that we reliably catch
        // buffer overflows.
        std::vector<char> bytes(length);
        in.read(bytes.data(), bytes.size());
        assert(in);
        LLVMFuzzerTestOneInput(
            reinterpret_cast<unsigned char const*>(bytes.data()),
            bytes.size());
        std::cout << argv[i] << " successful" << std::endl;
    }
    return 0;
}