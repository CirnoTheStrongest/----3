INCDIR := inc
SRCDIR := src
OUTDIR := out
UNITDIR := unit_tests

# Пути, по которым будет производится поиск исходных файлов
vpath %.c $(SRCDIR) $(UNITDIR)

# Компилятор
CC := gcc

# Стандартные библиотеки 
CFLAGS := -std=c99 -I $(INCDIR) -Wall -Wextra -Wfloat-equal -Wfloat-conversion -Wpedantic

# Библиотеки, подключаемые при модульном тестировании
UNITFLAGS := -lcheck -lpthread -lrt -lm

# Список исходных файлов основной программы
SRCS := $(wildcard $(SRCDIR)/*.c)

# Список исходных файлов модульных тестов
TEST_SRCS := $(wildcard $(UNITDIR)/*.c)

# Список всех .o файлов, получаемых из исходных в SRCDIR
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OUTDIR)/%.o)

# Список всех .o файлов для основной программы
OBJS_MAIN := $(filter-out $(OUTDIR)/sort_compare.o, $(OBJS))

# Список всех .o файлов для измерения времени работы сортировок
OBJS_SORT := $(filter-out $(OUTDIR)/main.o, $(OBJS))

# Объектные файлы для модульных тестов
OBJS_TEST := $(filter-out $(OUTDIR)/main.o, $(OBJS_MAIN) $(TEST_SRCS:$(UNITDIR)/%.c=$(OUTDIR)/%.o))

.PHONY: release debug func unit clean sort_cmp

release: CFLAGS += -O3
release: app.exe

debug: CFLAGS += -O0 -g3
debug: app.exe

func: debug
	./func_tests/scripts/func_tests.sh

unit: unit_tests.exe
	./unit_tests.exe

sort_cmp: sort_compare.exe
	./sort_compare.exe

app.exe: $(OBJS_MAIN)
	$(CC) $(CFLAGS) $^ -o $@

unit_tests.exe: $(OBJS_TEST)
	$(CC) $^ -o $@ $(UNITFLAGS)

sort_compare.exe: $(OBJS_SORT)
	$(CC) $(CFLAGS) $^ -o $@

$(OUTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -fr $(OUTDIR)
	rm -f ./*.exe 
