#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class textblock {
public:
  string line;
  vector <string> text;
  void setBlock () {
    cout << "Enter line ->" << endl;
    do
    {
      getline(cin,line);
      text.push_back(line);
    } while(!line.empty());
  }
  void getBlock () {
    cout << "text -> ";
    for (size_t i = 0; i < text.size(); i++) {
      cout << text[i] << endl;
    }
  }

  void getNLines() {
    cout << "Number of lines: " << text.size()-1 << endl;
  }
  void getLineN() {
    cout << "Which line to show ->";
    int n;
    scanf("%d", &n);
    n--;
    cout << "Line " << n+1 << " :" << text[n] << endl;
  }
  void getLexsems() {
    int n;
    cout << "Enter number of line to get number of lexems ->";
    scanf("%d", &n);
    n--;
    int count = 0;
    for (int i = 0; i < text[n].size(); i++) {
      char c = text[n][i];
      if (c == ' ') {
        count++;
      }
    }
    cout << "Lexsems of "<< n+1 << " line :" << count+1 << endl;
  }
  void getNLexsem() {
    int n;
    cout << "Enter number of line to get lexem ->";
    scanf("%d", &n);
    n--;
    int lex;
    cout << "Enter number of lexsem to show ->";
    scanf("%d", &lex);


    int count = 0;
    cout << lex << "'d lexem of " << n+1 << " line: ";
    for (int i = 0; i < text[n].size(); i++) {
      char c = text[n][i];
      if (c == ' ') {
        count++;
      }
      if (count+1 == lex) cout << c;
    }
    cout << endl;
  }
};

class EditableText : public textblock {

public:
  EditableText(textblock par){
    text = par.text;
  }

  void replaceLine() {
    int a;
    cout << "Number of line to remove ->";
    scanf("%d", &a);
    cout << "New line ->";
    cin.ignore();
    getline (cin, line);
    text[a-1] = line;
  }

  void replaceLexem() {
    int a, b;
    cout << "Number of line to remove lexem ->";
    scanf("%d", &a);
    cout << "Number of lexem to remove ->";
    scanf("%d", &b);

    a--;
    int len = 0;
    int pos;
    int count = 0;
    for (int i = 0; i < text[a].size(); i++) {
      char c = text[a][i];
      if (c == ' ') {
        count++;
      }
      if ((count+1 == b) && (c == ' ')) {
        pos = i;
      }
      if (count+1 == b) {
        len++;
      }
    }

    cout << "New lexem ->";
    cin.ignore();
    getline (cin, line);


    text[a].replace(pos+1, len, line);
    cout << "New " << a+1 << " line: " << text[a];


  }
};



int main(void)
{
  textblock t;
  t.setBlock();

  t.getNLines();
  t.getLineN();
  t.getLexsems();
  t.getNLexsem();

  EditableText* et = new EditableText(t);
  EditableText etext = *et;

  etext.replaceLine();
  etext.getBlock();
  etext.replaceLexem();

  return 0;
}
