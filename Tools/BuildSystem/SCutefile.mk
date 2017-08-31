project a b c
compile cxx g++
compile cxxflags -std=c++11 -I.. -I../..
compile c gcc
#fdf
a.target VariantTest
b.target ColorTableTest
c.target LoggerTest
a {
	../../Test/VariantTest.cpp
	../../SNVariant/Variant.cpp
}
b{
	../../Test/ColorTableTest.cpp
	../../SNLogger/ColorOutput/ColorTable.cpp
}

c {
	../../Test/LoggerTest.cpp
	../../SNLogger/ColorOutput/ColorTable.cpp
	../../SNLogger/Logger.cpp
	../../SNLogger/FormatLogger.cpp
}
