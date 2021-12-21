#include <iostream>
#include <bits/stdc++.h>
#include "include/Scanner.h"
#include "include/Renderer.h"
#include "include/AbstractSyntaxTree.h"

using namespace std;

int main(int argc, char* argv[]) {

	Scanner scanner;
	Renderer renderer;

	if (argc > 1) {
		if (argc > 2) {
			cout << "Error: MarkdownParser accepts only 1 argument => Mardown String\n";
			cout << "  Example: .\\MarkdownParser.exe \"#heading1\"\n";
			cout << "  Output:  <h1>heading1</h1>\n";
			return 0;
		}
		
		string inputMarkdownString = argv[1];
		string outputHTML = renderer
												.renderAbstractSyntaxTree(
													new AbstractSyntaxTree(
														scanner.scan(inputMarkdownString)
													)
												);

		cout << "  Markdown String: " << inputMarkdownString << "\n";
		cout << "  HTML: " << outputHTML << "\n";
		return 0;
	}


	// Help
	cout << "\nUsage: MarkdownParser.exe <MarkdownString>\n\n";
	cout << "  Simple Example:\n";
	cout << "    Command: .\\MarkdownParser.exe \"#heading1\"\n";
	cout << "    Output:  <h1>heading1</h1>\n\n";
	cout << "  Complex Example:\n";
	cout << "    Command: .\\MarkdownParser.exe \"##_A parser for Markdown Syntax_**Fast**and_Simple_\"\n";
	cout << "    Output:  <h2><em>A parser for Markdown Syntax</em><b>Fast</b>and<em>Simple</em></h2>\n\n";

	vector <string> markdownStrings = {
		"#heading-1",
		"##heading-2",
		"###heading-3",
		"####heading-4",
		"#####heading-5",
		"######heading-6",
		"_italic string with underscore_",
		"*italic string with asterisk*",
		"__bold string with underscore__",
		"**bold string with asterisk**",
		"~~strikethrough string~~",
		"`some inline code`",
		"```some multiline code```"
	};

	cout << "Currently Supported: {" << endl;
	for (string &str: markdownStrings) {
		cout << "  " << str << " => " << renderer.renderAbstractSyntaxTree(new AbstractSyntaxTree(scanner.scan(str))) << endl;
	}
	cout << "}\n" << endl;

	cout << "Github: https://github.com/Eessh/markdown-parser\n\n";

	return 0;
}