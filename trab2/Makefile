CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = agenda
SOURCES = main.cpp utils.cpp datetime.cpp appointments.cpp linked_list.cpp sorting.cpp \
          comparators.cpp agenda_parser.cpp scheduler.cpp file_writer.cpp result_calculator.cpp
HEADERS = utils.h datetime.h appointments.h linked_list.h sorting.h comparators.h \
          agenda_parser.h scheduler.h file_writer.h result_calculator.h
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
	rm -rf resultados

.PHONY: clean run