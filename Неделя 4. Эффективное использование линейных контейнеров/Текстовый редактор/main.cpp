#include <string>
#include <string_view>
#include <list>

#include "test_runner.h"
//#include "../../common/test_runner.h"

using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor(): currentPosition(0), currentIterator(text.begin()) {}

  void Left() {
    if(currentPosition == 0) return;
    --currentPosition, --currentIterator;
  }
  void Right() {
    if(currentPosition == text.size()) return;
    ++currentPosition, ++currentIterator;
  }

  void Insert(char token) {
    text.insert(currentIterator, token);
    ++currentPosition;
  }

  void Cut(size_t tokens = 1) {
    buffer.clear();
    if(text.empty()) return;

    auto fromIterator = currentIterator;
    auto endIterator = getN(tokens);

    buffer = std::string(fromIterator, endIterator);
    currentIterator = endIterator;
    text.erase(fromIterator, endIterator);
  }

  void Copy(size_t tokens = 1) {
    buffer.clear();
    if(text.empty()) return;
    buffer = std::string(currentIterator, getN(tokens));
  }
  void Paste() {
    if(buffer.empty()) return;
    text.insert(currentIterator, buffer.begin(), buffer.end());
    currentPosition += buffer.size();
  }

  string GetText() const {
    return {text.begin(), text.end()};
  }
private:
  list<char>::iterator getN(size_t tokens) {
    auto endIterator = currentIterator;
    if(currentPosition + tokens > text.size()) {
      endIterator = text.end();
    } else {
      while(tokens--) {
        ++endIterator;
      }
    }
    return endIterator;
  }

  size_t currentPosition;

  list<char> text;
  list<char>::iterator currentIterator;

  string buffer;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}