BT=boot
KER=kernel

all:boot_ KERNEL_

boot_:
	make -C $(BT)

KERNEL_:
	make -C $(KER)

	
clean:
	make -C $(BT) clean
	make -C $(KER) clean
