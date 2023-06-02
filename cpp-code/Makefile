# run with make n=2 k=1

all:
	$(MAKE) compileandrun && echo ""
	$(MAKE) clean

compileandrun:
	$(MAKE) compile && echo "" && $(MAKE) run && echo ""

clean:
	rm lexb

compile:
	g++ *.cpp -std=c++17 -o lexb

run:
	./lexb $(n) $(k)
