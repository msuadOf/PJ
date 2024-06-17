TARGET?=a1 a2 a3 a4 a5# b1 b2
all: $(patsubst %,all_%,$(TARGET))

all_%:
	@$(MAKE) -C $*

run: $(patsubst %,all_%,$(TARGET))

run_%:
	@$(MAKE) -C $* run

# 定义一个伪目标来遍历真实目标并执行它们
test: $(patsubst %,test_%,$(TARGET))

# 使用模式规则为每个目标创建一个测试规则
test_%:
	@$(MAKE) -C $* test

clean: $(patsubst %,clean_%,$(TARGET))

clean_%:
	@$(MAKE) -C $* clean

mv:
	mv a1.cpp a1
	mv a2.cpp a2
	mv a3.cpp a3
	mv a4.cpp a4
	mv a5.cpp a5
	mv b1.cpp b1
	mv b2.cpp b2

cp:
	cp Makefile a1
	cp Makefile a2
	cp Makefile a3
	cp Makefile a4
	cp Makefile a5
	cp Makefile b1
	cp Makefile b2

	cp conio.c a1
	cp conio.c a2
	cp conio.c a3
	cp conio.c a4
	cp conio.c a5
	cp conio.c b1
	cp conio.c b2

	cp conio.h a1
	cp conio.h a2
	cp conio.h a3
	cp conio.h a4
	cp conio.h a5
	cp conio.h b1
	cp conio.h b2