#include "Renderer.hpp"

Renderer::Renderer() {
  this->iterator = nullptr;
}

std::string Renderer::render(const MarkdownParser::AST* ast) {
  std::string contentStr;
  if (ast == nullptr) {
    #ifdef DEBUG
    std::cout << "Warn: std::string Renderer::render(const MarkdownParser::AST* ast), ast = nullptr. Returning empty HTML string.\n";
    #endif
    return contentStr;
  }
  const MarkdownParser::ASTNode* root = ast->root();
  for (const MarkdownParser::ASTNode* child: root->children) {
    contentStr.append(this->recursiveASTRenderer(child));
  }
  return contentStr;
}

std::string Renderer::recursiveASTRenderer(const MarkdownParser::ASTNode* node) {
  std::string contentStr;
  if (node == nullptr) {
    #ifdef DEBUG
    std::cout << "Warn: const std::string& Renderer::recursiveASTRenderer(const MarkdownParser::ASTNode* node), node = nullptr, Returning empty HTML string.\n";
    #endif
    return contentStr;
  }
  for (const MarkdownParser::ASTNode* child: node->children) {
    contentStr.append(this->recursiveASTRenderer(child));
  }
  switch (node->token.type()) {
    case MarkdownParser::TokenType::HEADING: {
      const std::vector<std::pair<std::string, std::string>> tags = {
        { "<h1>", "</h1>" },
        { "<h2>", "</h2>" },
        { "<h3>", "</h3>" },
        { "<h4>", "</h4>" },
        { "<h5>", "</h5>" },
        { "<h6>", "</h6>" }
      };
      contentStr = tags[node->token.level()-1].first + contentStr + tags[node->token.level()-1].second;
      break;
    }
    case MarkdownParser::TokenType::BOLD_ITALIC: {
      if (node->token.level() == 1) {
        contentStr = "<em>" + contentStr + "</em>";
      }
      else if (node->token.level() == 2) {
        contentStr = "<strong>" + contentStr + "</strong>";
      }
      else {
        #ifdef DEBUG
        std::cout << "Error: Encountered a token of type BOLD_ITALIC, with level: " << node->token.level() << ".\n";
        #endif
      }
      break;
    }
    case MarkdownParser::TokenType::CODE: {
      if (node->token.level() == 1) {
        contentStr = "<code>" + contentStr + "</code>";
      }
      else if (node->token.level() == 3) {
        contentStr = "<pre><code>" + contentStr + "</code></pre>";
      }
      else {
        #ifdef DEBUG
        std::cout << "Error: Encountered a token of type CODE, with level: " << node->token.level() << ".\n";
        #endif
      }
      break;
    }
    case MarkdownParser::TokenType::STRIKETHROUGH: {
      contentStr = "<del>" + contentStr + "</del>";
      break;
    }
    case MarkdownParser::TokenType::QUOTE: {
      contentStr = "<div class=\"quote\">" + contentStr + "</div>";
      break;
    }
    case MarkdownParser::TokenType::TEXT: {
      // contentStr = "<p>" + node->token.value() + "</p>";
      contentStr = node->token.value();
      break;
    }
    case MarkdownParser::TokenType::NEWLINE: {
      contentStr = "<br>";
      break;
    }
    default: {
      #ifdef DEBUG
      std::cout << "Error: Encountered a token of type: " << MarkdownParser::tokenTypeToStr(node->token.type()) << ", which is not renderable.\n";
      #endif
      break;
    }
  }
  return contentStr;
}