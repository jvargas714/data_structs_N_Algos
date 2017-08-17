include config.vars

dirs=./Algos ./data_structs

all:
	for i in $(dirs); do \
		echo "Building $$i"; \
		make -C $$i -f makefile all ; \
	done 

clean:
	for i in $(dirs); do \
		echo "cleaning $$i"; \
		make -C $$i -f makefile all; \
	done
