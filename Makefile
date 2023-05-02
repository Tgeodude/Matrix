CXX = gcc++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

LIB_NAME = s21_matrix_opp

SRCS = $(wildcard s21_*.cpp)

OBJS = $(SRCS:.c=.o)

all: $(LIB_NAME).a test clean

%.o: %.c 
		$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
		ar rc $(LIB_NAME).a $^
		randlib $(LIB_NAME)
		rm -rf *.o

test: 
		@rm -rf build
		@mkdir build
		@cd build && cmake ../ && make && ./main

clean:
		rm -rf *.o test *.a