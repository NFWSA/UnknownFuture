# This is a demo for my UnknownFuture repo
project a b c d e FormatStringTest
compile cxx g++
compile cxxflags -std=c++1z -Isrc -ggdb -DWIN64
compile c gcc
#fdf
a.target VariantTest
a.path Build/Test
b.path Build/Test
c.path Build/Test
d.path  Build/Test
e.path Build/Test
FormatStringTest.path Build/Test

b.target ColorTableTest
c.target LoggerTest
d.target ConfigTest
e.target StateMachine

a {
	Test/VariantTest.cpp
	src/SNVariant/Variant.cpp
}
b{
	Test/ColorTableTest.cpp
	src/SNLogger/ColorOutput/ColorTable.cpp
}

c {
	Test/LoggerTest.cpp
	src/SNLogger/ColorOutput/ColorTable.cpp
	src/SNLogger/Logger.cpp
	src/SNLogger/FormatLogger.cpp
}
d{Test/ConfigTest.cpp
	src/SNConfig/Reader/ConfigReader.cpp
	src/SNVariant/Variant.cpp
}

e {
	Test/StateMachineTest.cpp
	# src/SNStateMachine.
}
FormatStringTest {
	Test/FormatStringTest.cpp
	src/SNString/FormatString.cpp
	src/SNVariant/Variant.cpp
	src/SNConfig/Reader/ConfigReader.cpp
}
