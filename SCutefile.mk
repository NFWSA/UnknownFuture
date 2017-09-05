# This is a demo for my UnknownFuture repo
project a b c d
compile cxx g++
compile cxxflags -std=c++11 -I. -ggdb
compile c gcc
#fdf
a.target VariantTest
a.path Build/Test
b.path Build/Test
c.path Build/Test
d.path  Build/Test
b.target ColorTableTest
c.target LoggerTest
d.target ConfigTest
a {
	Test/VariantTest.cpp
	SNVariant/Variant.cpp
}
b{
	Test/ColorTableTest.cpp
	SNLogger/ColorOutput/ColorTable.cpp
}

c {
	Test/LoggerTest.cpp
	SNLogger/ColorOutput/ColorTable.cpp
	SNLogger/Logger.cpp
	SNLogger/FormatLogger.cpp
}
d{Test/ConfigTest.cpp
	SNConfig/Reader/ConfigReader.cpp
	SNVariant/Variant.cpp
}
