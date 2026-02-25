
.PHONY: all clean

########################################
# 1. FIRST FUNCTIONS – subst
########################################

bar1 := $(subst not,totally,"I am not superman")

# Thay space bằng comma
comma := ,
empty :=
space := $(empty) $(empty)

foo1 := a b c
bar2 := $(subst $(space),$(comma),$(foo1))

# SAI: có space trong tham số
bar2_wrong := $(subst $(space), $(comma) , $(foo1))

########################################
# 2. STRING SUBSTITUTION – patsubst & shorthand
########################################

foo2 := a.o b.o l.a c.o

one   := $(patsubst %.o,%.c,$(foo2))
two   := $(foo2:%.o=%.c)
three := $(foo2:.o=.c)

########################################
# 3. FOREACH FUNCTION
########################################

foo3 := who are you
bar3 := $(foreach w,$(foo3),$(w)!)

########################################
# 4. IF FUNCTION
########################################

foo4 := $(if this-is-not-empty,then!,else!)
empty_var :=
bar4 := $(if $(empty_var),then!,else!)

########################################
# 5. CALL FUNCTION (user-defined function)
########################################

sweet_new_fn = Variable Name: $(0) First: $(1) Second: $(2) Empty Variable: $(3)

########################################
# 6. SHELL FUNCTION
########################################

shell_demo := $(shell echo "hello"; echo "world")

########################################
# 7. FILTER / FILTER-OUT
########################################

files := foo.c bar.h main.c test.o util.o test_main.o

only_o      := $(filter %.o,$(files))
only_c_h    := $(filter %.c %.h,$(files))
no_headers  := $(filter-out %.h,$(files))
no_test_o   := $(filter %.o,$(filter-out test%,$(files)))

########################################
# ALL TARGET – SHOW EVERYTHING
########################################

all:
	@echo "===== 1. subst ====="
	@echo "bar1 = $(bar1)"
	@echo "bar2 = $(bar2)"
	@echo "bar2_wrong = $(bar2_wrong)"
	@echo

	@echo "===== 2. patsubst & shorthand ====="
	@echo "one   = $(one)"
	@echo "two   = $(two)"
	@echo "three = $(three)"
	@echo

	@echo "===== 3. foreach ====="
	@echo "bar3 = $(bar3)"
	@echo

	@echo "===== 4. if ====="
	@echo "foo4 = $(foo4)"
	@echo "bar4 = $(bar4)"
	@echo

	@echo "===== 5. call ====="
	@echo "$(call sweet_new_fn,go,tigers)"
	@echo

	@echo "===== 6. shell ====="
	@echo "shell_demo = $(shell_demo)"
	@echo

	@echo "===== 7. filter ====="
	@echo "only_o     = $(only_o)"
	@echo "only_c_h   = $(only_c_h)"
	@echo "no_headers = $(no_headers)"
	@echo "no_test_o  = $(no_test_o)"

clean:
	@echo "Nothing to clean"

