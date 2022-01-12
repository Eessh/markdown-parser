default:
	g++ MarkdownParser.cpp src/*.cpp -O3 -o MarkdownParser.exe

run:
	./MarkdownParser.exe

build_run:
	g++ MarkdownParser.cpp src/*.cpp -O3 -o MarkdownParser.exe && .\MarkdownParser.exe

clean:
	del .\MarkdownParser.exe

build_run_clean:
	g++ MarkdownParser.cpp src/*.cpp -O3 -o MarkdownParser.exe && .\MarkdownParser.exe && del .\MarkdownParser.exe
