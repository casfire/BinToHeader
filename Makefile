.PHONY: all clean
all:
	@echo "Compiling..."
	@g++ main.cpp -Wall -Wextra -O -o BinToHeader
	@echo "Done."

clean:
	@rm -rf BinToHeader BinToHeader.exe
	@echo "Cleaned."
