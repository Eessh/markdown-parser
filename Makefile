default:
	g++ -std=c++17 -O3 \
	MarkdownParser.cpp src/*.cpp \
	-o MarkdownParser.exe

run:
	./MarkdownParser.exe

build_run:
	g++ -std=c++17 -O3 \
	MarkdownParser.cpp src/*.cpp \
	-o MarkdownParser.exe \
	&& \
	.\MarkdownParser.exe

clean:
	del .\MarkdownParser.exe

build_run_clean:
	g++ -std=c++17 -O3 \
	MarkdownParser.cpp src/*.cpp \
	-o MarkdownParser.exe \
	&& \
	.\MarkdownParser.exe \
	&& \
	del .\MarkdownParser.exe
