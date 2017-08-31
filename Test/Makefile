CXX = g++
CC = g++
CXXFLAGS = --std=c++11 -I.. -Wall
all: ColorTableTest LoggerTest VariantTest

VariantTest: VariantTest.o Variant.o
ColorTableTest: ColorTableTest.o ColorTable.o
LoggerTest: LoggerTest.o Logger.o FormatLogger.o ColorTable.o
Variant.o: ../SNVariant/Variant.cpp
	$(CXX) $(CXXFLAGS) -c -o Variant.o ../SNVariant/Variant.cpp
ColorTable.o: ../SNLogger/ColorOutput/ColorTable.cpp
	$(CXX) $(CXXFLAGS) -c -o ColorTable.o ../SNLogger/ColorOutput/ColorTable.cpp
Logger.o: ../SNLogger/Logger.cpp
	$(CXX) $(CXXFLAGS) -c -o Logger.o ../SNLogger/Logger.cpp
FormatLogger.o: ../SNLogger/FormatLogger.cpp
	$(CXX) $(CXXFLAGS) -c -o FormatLogger.o ../SNLogger/FormatLogger.cpp
