# Markdown Parser
A simple tool to parse the Mardown and, convert it to HTML.

#### TODO
- [x] Headings
- [x] Bold
- [x] Italic
- [x] Nested Bold and Italic
- [ ] All Bold and Italic
- [x] Strikethrough
- [x] Inline Code
- [ ] Multiline Code
- [ ] Quote
- [ ] Lists
- [ ] Links
- [ ] Images
- [ ] Tables

#### To run locally:
```bash
git clone https://github.com/Eessh/markdown-parser.git
cd markdown-parser/
make
make run
```

#### If you are on Unix based OS (Linux, macOS) you should be changing the Makefile:
```Makefile
default:
	g++ MarkdownParser.cpp src/*.cpp -o MarkdownParser

run:
	./MarkdownParser

build_run:
	g++ MarkdownParser.cpp src/*.cpp -o MarkdownParser && ./MarkdownParser

clean:
	rm ./MarkdownParser

build_run_clean:
	g++ MarkdownParser.cpp src/*.cpp -o MarkdownParser && ./MarkdownParser && rm ./MarkdownParser
```
