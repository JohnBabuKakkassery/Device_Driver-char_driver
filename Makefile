SRC_DIR := source
BIN_DIR := bin

all:
	mkdir -p $(BIN_DIR)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/$(SRC_DIR) modules
	mv $(SRC_DIR)/*.ko $(BIN_DIR)/

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/$(SRC_DIR) clean
	rm -rf $(BIN_DIR)

