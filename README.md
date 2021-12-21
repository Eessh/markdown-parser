# Markdown Parser
A simple tool to parse the Mardown and, convert it to HTML.

### Build:
```bash
git clone https://github.com/Eessh/markdown-parser.git
cd markdown-parser/
make
```
❗ Linux / macOS users should change the Makefile, see the last portion.

### Usage:
- Windows
```powershell
.\MarkdownParser.exe <MarkdownString>

Example:
> .\MarkdownParser.exe "###Hi, I'm __*Eessh*__"
>   MarkdownString: "###Hi, I'm __*Eessh*__"
>   HTML: "<h4>Hi, I'm <b><em>Eessh</em></b></h4>"
```
- Linux / macOS
```bash
./MarkdownParser <MarkdownString>

Example:
> ./MarkdownParser "###Hi, I'm __*Eessh*__"
>   MarkdownString: "###Hi, I'm __*Eessh*__"
>   HTML: "<h4>Hi, I'm <b><em>Eessh</em></b></h4>"
```

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
