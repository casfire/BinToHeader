.PHONY: all clean
all:
	@echo "Compiling..."
	@gcc main.c -Wall -Wextra -O -o BinToHeader
	@echo "Done."

clean:
	@rm -rf BinToHeader BinToHeader.exe
	@echo "Cleaned."
