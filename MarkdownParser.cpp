#include <iostream>
#include <bits/stdc++.h>
#include "include/Scanner.h"
#include "include/Renderer.h"
#include "include/AbstractSyntaxTree.h"

using namespace std;

int main() {
	// string markdownStr = "##_A parser for Markdown Syntax_**Fast**and_Simple_";
	// string markdownStr;
	// getline(cin, markdownStr);
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
	Scanner scanner;
	Renderer renderer;
	cout << "{" << endl;
	for (string &str: markdownStrings) {
		cout << "\tHTML: " << renderer.renderAbstractSyntaxTree(new AbstractSyntaxTree(scanner.scan(str))) << endl;
	}
	cout << "}" << endl;

	string markdownStr = "##_A parser for Markdown Syntax_**Fast**and_Simple_";
	string html = renderer
								.renderAbstractSyntaxTree(
									new AbstractSyntaxTree(
										scanner.scan(markdownStr)
									)
								);
	cout << "Complex HTML: " << html << endl;
	return 0;
}