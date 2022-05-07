#!/bin/sh
set -e

pushd ..

if [ ! -d "build/Bindings" ]; then
    cmake -S . -B build -G Ninja -D GENERATE_BINDINGS=ON
    cmake --build build
fi

cp swig/Bindings.csproj.template build/Bindings/Bindings.csproj
mkdir -p build/feed

pushd build/Bindings
dotnet build -c Release
nuget add bin/Release/Bindings.1.0.0.nupkg -source ../feed
popd

nuget locals global-packages -clear

pushd DemoCS
dotnet add package Bindings -s ../build/feed
dotnet build
popd

popd