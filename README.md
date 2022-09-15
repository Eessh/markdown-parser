# Markdown Parser
A header only library to parse Markdown to AST (Abstract Syntax Tree).

> Header file `MarkdownParser.hpp` can be found at `/NewVersion/plugins/MarkdownToHTML/MarkdownParser.hpp`, you may click [here](https://github.com/Eessh/markdown-parser/blob/master/NewVersion/plugins/MarkdownToHTML/MarkdownParser.hpp)😄

Currently old code is being abstracted and moved to NewVersion. The HTML rendering part will be a plugin(`/NewVersion/plugins/MarkdownToHTML`).

### Build:
```bash
git clone https://github.com/Eessh/markdown-parser.git
cd markdown-parser/
make
```
❗ [Linux / macOS users](#unixMakefile) should change the Makefile, see the last portion.

### Usage:
- Windows
```powershell
.\MarkdownParser.exe <MarkdownString>

Example:
> .\MarkdownParser.exe "###Hi, I'm __*Eessh*__"
>   MarkdownString: "###Hi, I'm __*Eessh*__"
>   HTML: "<h3>Hi, I'm <b><em>Eessh</em></b></h3>"
```
- Linux / macOS
```bash
./MarkdownParser <MarkdownString>

Example:
> ./MarkdownParser "###Hi, I'm __*Eessh*__"
>   MarkdownString: "###Hi, I'm __*Eessh*__"
>   HTML: "<h3>Hi, I'm <b><em>Eessh</em></b></h3>"
```

#### TODO
- [x] Headings
- [x] Bold
- [x] Italic
- [x] Nested Bold and Italic
- [x] All Bold and Italic
- [x] Strikethrough
- [x] Inline Code
- [x] Multiline Code
- [x] Quote
- [ ] Lists
- [ ] Links
- [ ] Images
- [ ] Tables

#### <a name="unixMakefile"></a> If you are on Unix based OS (Linux, macOS) you should be changing the Makefile:
```Makefile
default:
	g++ MarkdownParser.cpp src/*.cpp -O3 -o MarkdownParser

run:
	./MarkdownParser

build_run:
	g++ MarkdownParser.cpp src/*.cpp -O3 -o MarkdownParser && ./MarkdownParser

clean:
	rm ./MarkdownParser

build_run_clean:
	g++ MarkdownParser.cpp src/*.cpp -O3 -o MarkdownParser && ./MarkdownParser && rm ./MarkdownParser
```
