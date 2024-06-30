WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --leak-check=full --verbose

SRCS = Window_Manager_ArnavSrivastava.c
OBJS = $(SRCS:%.c=%.o)
TARGET = Window_Manager

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(GCC) -c $*.c

testmem0: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_0.txt

testmem1: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_1.txt

testmem2: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_2.txt

testmem3: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_3.txt

testmem4: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_4.txt

testmem5: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_5.txt

testmem6: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_6.txt

testmem7: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_7.txt

testmem8: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_8.txt

testmem9: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_9.txt

testmem10: $(TARGET)
	$(VAL) ./$(TARGET) examples/testcase_10.txt

test0: $(TARGET)
	./$(TARGET) examples/testcase_0.txt

test1: $(TARGET)
	./$(TARGET) examples/testcase_1.txt

test2: $(TARGET)
	./$(TARGET) examples/testcase_2.txt

test3: $(TARGET)
	./$(TARGET) examples/testcase_3.txt

test4: $(TARGET)
	./$(TARGET) examples/testcase_4.txt

test5: $(TARGET)
	./$(TARGET) examples/testcase_5.txt

test6: $(TARGET)
	./$(TARGET) examples/testcase_6.txt

test7: $(TARGET)
	./$(TARGET) examples/testcase_7.txt

test8: $(TARGET)
	./$(TARGET) examples/testcase_8.txt

test9: $(TARGET)
	./$(TARGET) examples/testcase_9.txt

test10: $(TARGET)
	./$(TARGET) examples/testcase_10.txt

testall: test0 test1 test2 test3 test4 test5 test6 test7 test8 test9 test10

testallmem: testmem0 testmem1 testmem2 testmem3 testmem4 testmem5 testmem6 testmem7 testmem8 testmem9 testmem10

clean:
	rm -f $(TARGET) *.o memcheck.txt *~
