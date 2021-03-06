ifneq ($(KERNELRELEASE),)
kbench9000-y := main.o curve25519-u128.o
obj-m := kbench9000.o
ccflags-y += -O3
ccflags-y += -D'pr_fmt(fmt)=KBUILD_MODNAME ": " fmt'
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default: build

run: build
	sudo ./run.sh
build:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
.PHONY: default run build clean
endif

