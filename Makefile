END += .out
LIB += -lboost_system -lboost_thread -lpthread

all:
	g++ teste_cliente.cpp -o cliente$(END) $(LIB)

clean:
	rm *$(END)