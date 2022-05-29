OBJS = main.o CMatrix.o CDenseMatrix.o CSparseMatrix.o CMatrixInterface.o CLibUtil.o CCommand.o

CXX = g++

CXXFLAGS = -w -Wall -std=c++11 -pedantic -Wno-long-long -Werror -O0 -ggdb -g

EXECUTABLE = zarubal1

all : compile doc

compile : $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXECUTABLE)

main.o: $($(CXX) -MM src/main.cpp) src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o main.o

CMatrix.o: $($(CXX) -MM src/CMatrix.cpp) src/CMatrix.cpp
	$(CXX) $(CXXFLAGS) -c src/CMatrix.cpp -o CMatrix.o

CDenseMatrix.o: $($(CXX) -MM src/CDenseMatrix.cpp) src/CDenseMatrix.cpp
	$(CXX) $(CXXFLAGS) -c src/CDenseMatrix.cpp -o CDenseMatrix.o

CSparseMatrix.o: $($(CXX) -MM src/CSparseMatrix.cpp) src/CSparseMatrix.cpp
	$(CXX) $(CXXFLAGS) -c src/CSparseMatrix.cpp -o CSparseMatrix.o

CMatrixInterface.o: $($(CXX) -MM src/CMatrixInterface.cpp) src/CMatrixInterface.cpp
	$(CXX) $(CXXFLAGS) -c src/CMatrixInterface.cpp -o CMatrixInterface.o

CLibUtil.o: $($(CXX) -MM src/CLibUtil.cpp) src/CLibUtil.cpp
	$(CXX) $(CXXFLAGS) -c src/CLibUtil.cpp -o CLibUtil.o

CCommand.o: $($(CXX) -MM src/CCommand.cpp) src/CCommand.cpp
	$(CXX) $(CXXFLAGS) -c src/CCommand.cpp -o CCommand.o

doc :
	doxygen Doxyfile > /dev/null

clean :
	rm -r ./*.o ${EXECUTABLE} doc

run :
	./${EXECUTABLE}
