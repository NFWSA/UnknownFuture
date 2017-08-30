project a b c
compile cxx g++
compile cxxflags -std=c++11
compile c gcc
#fdf
c {
	./../a.c
	b.c
	c.cpp
}

c.target d
c.path ./

b{
	c.c
}
