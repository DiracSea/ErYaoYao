CPP := g++
CC := gcc
VPATH := src 
INIT := Init.o
VL := Validate.o
MN := main_2_p4.o
TARGETS := pb1 pb2 1_p1p2 1_p3 2_p3 2_p3_1 2_p4

all: $(TARGETS)

pb1: main_b.o dg_b.o dg_p1.o IO.o $(VL) $(INIT)
		$(CPP) -o $@ $^
		
pb2: main_b1.o dg_b.o dg_p1.o dg_p4.o IO.o $(VL) $(INIT)
		$(CPP) -o $@ $^

1_p1p2: main_1_p1p2.o dg_p1.o IO.o $(VL) $(INIT) 
		$(CPP) -o $@ $^

1_p3: main_1_p3.o dg_p1.o IO.o $(VL) $(INIT) 
		$(CPP) -o $@ $^

2_p3: main_2_p3.o dg_p3.o dg_p1.o IO.o $(VL) $(INIT) 
		$(CPP) -o $@ $^

2_p3_1: main_2_p3_1.o dg_p3.o dg_p1.o IO.o $(VL) $(INIT) 
		$(CPP) -o $@ $^ 

2_p4: 
		$(CPP) -c -o Init.o src/Init.cpp -O0
		$(CPP) -c -o IO.o src/IO.cpp -O0 
		$(CPP) -c -o $(VL) src/Validate.cpp -O0 
		$(CPP) -c -o dg_p1.o src/dg_p1.cpp -O0 
		$(CPP) -c -o dg_p4.o src/dg_p4.cpp -O0 
		$(CPP) -c -o main_2_p4.o main_2_p4.cpp -O0
		$(CPP) -o 2_p4_0 main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O0 
		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o
		$(CPP) -c -o Init.o src/Init.cpp -O1
		$(CPP) -c -o IO.o src/IO.cpp -O1
		$(CPP) -c -o $(VL) src/Validate.cpp -O1
		$(CPP) -c -o dg_p1.o src/dg_p1.cpp -O1
		$(CPP) -c -o dg_p4.o src/dg_p4.cpp -O1 
		$(CPP) -c -o main_2_p4.o main_2_p4.cpp -O1
		$(CPP) -o 2_p4_1 main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O1 
		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o
		$(CPP) -c -o Init.o src/Init.cpp -O2
		$(CPP) -c -o IO.o src/IO.cpp -O2 
		$(CPP) -c -o $(VL) src/Validate.cpp -O2 
		$(CPP) -c -o dg_p1.o src/dg_p1.cpp -O2 
		$(CPP) -c -o dg_p4.o src/dg_p4.cpp -O2 
		$(CPP) -c -o main_2_p4.o main_2_p4.cpp -O2
		$(CPP) -o 2_p4_2 main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O2 
		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o
		$(CPP) -c -o Init.o src/Init.cpp -O3
		$(CPP) -c -o IO.o src/IO.cpp -O3 
		$(CPP) -c -o $(VL) src/Validate.cpp -O3 
		$(CPP) -c -o dg_p1.o src/dg_p1.cpp -O3 
		$(CPP) -c -o dg_p4.o src/dg_p4.cpp -O3 
		$(CPP) -c -o main_2_p4.o main_2_p4.cpp -O3
		$(CPP) -o 2_p4_3 main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O3 
		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o

# 2_p4_C: 
# 		$(CC) -c -o Init.o src/Init.cpp -O0
# 		$(CC) -c -o IO.o src/IO.cpp -O0 
# 		$(CC) -c -o $(VL) src/Validate.cpp -O0 
# 		$(CC) -c -o dg_p1.o src/dg_p1.cpp -O0 
# 		$(CC) -c -o dg_p4.o src/dg_p4.cpp -O0 
# 		$(CC) -c -o main_2_p4.o main_2_p4.cpp -O0
# 		$(CC) -o 2_p4_0_C main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O0 
# 		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o
# 		$(CC) -c -o Init.o src/Init.cpp -O1
# 		$(CC) -c -o IO.o src/IO.cpp -O1
# 		$(CC) -c -o $(VL) src/Validate.cpp -O1
# 		$(CC) -c -o dg_p1.o src/dg_p1.cpp -O1
# 		$(CC) -c -o dg_p4.o src/dg_p4.cpp -O1 
# 		$(CC) -c -o main_2_p4.o main_2_p4.cpp -O1
# 		$(CC) -o 2_p4_1_C main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O1 
# 		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o
# 		$(CC) -c -o Init.o src/Init.cpp -O2
# 		$(CC) -c -o IO.o src/IO.cpp -O2 
# 		$(CC) -c -o $(VL) src/Validate.cpp -O2 
# 		$(CC) -c -o dg_p1.o src/dg_p1.cpp -O2 
# 		$(CC) -c -o dg_p4.o src/dg_p4.cpp -O2 
# 		$(CC) -c -o main_2_p4.o main_2_p4.cpp -O2
# 		$(CC) -o 2_p4_2_C main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O2 
# 		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o
# 		$(CC) -c -o Init.o src/Init.cpp -O3
# 		$(CC) -c -o IO.o src/IO.cpp -O3 
# 		$(CC) -c -o $(VL) src/Validate.cpp -O3 
# 		$(CC) -c -o dg_p1.o src/dg_p1.cpp -O3 
# 		$(CC) -c -o dg_p4.o src/dg_p4.cpp -O3 
# 		$(CC) -c -o main_2_p4.o main_2_p4.cpp -O3
# 		$(CC) -o 2_p4_3_C main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o -O3 
# 		rm main_2_p4.o dg_p4.o dg_p1.o $(VL) IO.o Init.o
#2_b:

%.o: %.cpp $(HPP)
		$(CPP) -c $< -o $@

.PHONY: clean
clean:  
		rm -f *.o $(TARGETS)