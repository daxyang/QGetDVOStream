TARGET=libQGetDVOStream.so

CXX=g++

.PHONY:all

$(TARGET):QGetDVOStream.o
	$(CXX) -fPIC -O2 -pipe -shared -o $(TARGET) QGetDVOStream.o

QGetDVOStream.o:QGetDVOStream.cpp QGetDVOStream.h dvo_protocol.h
	$(CXX) -c QGetDVOStream.cpp QGetDVOStream.h dvo_protocol.h

install:
	cp -f $(TARGET)  /usr/local/lib

clean:
	rm -f *.o *.so
